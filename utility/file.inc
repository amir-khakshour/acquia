<?php
// $Id
/**
 * @file
 *  File manipulating and related functions
 */

 /**
 * Upload remote uri to drupal files
 * @param string $uri URI of resource to be uploaded
 * @param array $settings array of key => value based settings
 * @return 
 */
function acquia_upload_remote_uri($uri, $settings) {
 global $conf;

 // init settings array
 $settings +=array(
   'upload_location' => acquia_variable_get('upload_location', 'public://acquia/misc'),
   'file_validate_size' => acquia_variable_get('upload_max_size', NULL),
   'file_extensions' => acquia_variable_get('upload_file_extensions', 'png gif jpg txt'),
   'upload_validators' => array(),
   'permanent' => 0, //  save remote file permanently?
 );
  // Check that the destination is writable.
  $temporary_directory = 'temporary://';
  if (!file_prepare_directory($temporary_directory, FILE_MODIFY_PERMISSIONS)) {
    watchdog('file', '<ACQUIA::UTILITY::FILE>: The directory %directory is not writable, because it does not have the correct permissions set.', array('%directory' => drupal_realpath($temporary_directory)));
    drupal_set_message(t('<ACQUIA::UTILITY::FILE>: The file could not be transferred because the temporary directory is not writable.'), 'error');
    return;
  }

  // Check that the destination is writable.
  $directory = $settings['upload_location'];
  $mode = variable_get('file_chmod_directory', 0775);

  // This first chmod check is for other systems such as S3, which don't work
  // with file_prepare_directory().
  if (!drupal_chmod($directory, $mode) && !file_prepare_directory($directory, FILE_CREATE_DIRECTORY)) {
    watchdog('file', '<ACQUIA::UTILITY::FILE>: File %file could not be copied, because the destination directory %destination is not configured correctly.', array('%file' => $uri, '%destination' => drupal_realpath($directory)));
    drupal_set_message(t('<ACQUIA::UTILITY::FILE>: The specified file %file could not be copied, because the destination directory is not properly configured. This may be caused by a problem with file or directory permissions. More information is available in the system log.', array('%file' => $uri)), 'error');
    return;
  }

  // Check the headers to make sure it exists and is within the allowed size.
  $ch = curl_init();
  curl_setopt($ch, CURLOPT_URL, $uri);
  curl_setopt($ch, CURLOPT_VERBOSE, 1);  
  if (isset($conf['proxy_server']) && isset($conf['proxy_port'])) {	// If the $proxy variable is set, then
    curl_setopt($ch, CURLOPT_PROXY, $conf['proxy_server'] .':' .$conf['proxy_port']);
    curl_setopt($ch, CURLOPT_PROXYTYPE, 'HTTP');
  }
  curl_setopt($ch, CURLOPT_HEADER, TRUE);
  curl_setopt($ch, CURLOPT_NOBODY, TRUE);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
  curl_setopt($ch, CURLOPT_HEADERFUNCTION, '_acquia_remote_file_parse_header');
  // Causes a warning if PHP safe mode is on.
  @curl_setopt($ch, CURLOPT_FOLLOWLOCATION, TRUE);

  curl_exec($ch);
  $info = curl_getinfo($ch);
  if ($info['http_code'] != 200) {
    curl_setopt($ch, CURLOPT_HTTPGET, TRUE);
    $file_contents = curl_exec($ch);
    $info = curl_getinfo($ch);
  }
  if ($info['http_code'] != 200) {
    switch ($info['http_code']) {
      case 403:
        drupal_set_message(t('<ACQUIA::UTILITY::FILE>: The remote file could not be transferred because access to the file was denied.'));
        break;
      case 404:
        drupal_set_message(t('<ACQUIA::UTILITY::FILE>: The remote file could not be transferred because it was not found.'));
        break;
      default:
        drupal_set_message(t('<ACQUIA::UTILITY::FILE>: The remote file could not be transferred due to an HTTP error (@code).', array('@code' => $info['http_code'])));
    }
    return;
  }

  // Update the $uri variable to reflect any redirects.
  $uri = $info['url'];
  $uri_info = parse_url($uri);
  // Determine the proper filename by reading the filename given in the
  // Content-Disposition header. If the server fails to send this header,
  // fall back on the basename of the URL.
  //
  // We prefer to use the Content-Disposition header, because we can then
  // use URLs like http://example.com/get_file/23 which would otherwise be
  // rejected because the URL basename lacks an extension.
  $filename = _acquia_remote_file_filename();
  if (empty($filename)) {
    $filename = rawurldecode(basename($uri_info['path']));
  }

  $pathinfo = pathinfo($filename);

  // Create the file extension from the MIME header if all else has failed.
  if (empty($pathinfo['extension']) && $extension = _acquia_remote_file_mime_extension()) {
    $filename = $filename . '.' . $extension;
    $pathinfo = pathinfo($filename);
  }

  $filename = acquia_file_clean_filename($filename, $settings['file_extensions']);
  $filepath = file_create_filename($filename, $temporary_directory);

  if (empty($pathinfo['extension'])) {
    drupal_set_message(t('<ACQUIA::UTILITY::FILE>: The remote URL must be a file and have an extension.'));
    return;
  }

  // Perform basic extension check on the file before trying to transfer.
  $extensions = $settings['file_extensions'];
  $regex = '/\.('. preg_replace('/[ +]/', '|', preg_quote($extensions)) .')$/i';
  if (!empty($extensions) && !preg_match($regex, $filename)) {
    drupal_set_message(t('<ACQUIA::UTILITY::FILE>: Only files with the following extensions are allowed: %files-allowed.', array('%files-allowed' => $extensions)));
    return;
  }

  // Check file size based off of header information.
  if (!empty($settings['file_validate_size'])) {
    $max_size = $settings['file_validate_size'];
    $file_size = $info['download_content_length'];
    if ($file_size > $max_size) {
      drupal_set_message(t('<ACQUIA::UTILITY::FILE>: The remote file is %filesize exceeding the maximum file size of %maxsize.', array('%filesize' => format_size($file_size), '%maxsize' => format_size($max_size))));
      return;
    }
  }
  // Set progress bar information.
  $options = array(
    'key' => 'key-'.$filepath,
    'filepath' => $filepath,
  );
  acquia_remote_file_set_transfer_options($options);
  $transfer_success = FALSE;
  // If we've already downloaded the entire file because the header-retrieval
  // failed, just ave the contents we have.
  if (isset($file_contents)) {
    if ($fp = @fopen($filepath, 'w')) {
      fwrite($fp, $file_contents);
      fclose($fp);
      $transfer_success = TRUE;
    }
  }
  // If we don't have the file contents, download the actual file.
  else {
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, $uri);
    if (isset($conf['proxy_server']) && isset($conf['proxy_port'])) {	// If the $proxy variable is set, then
      curl_setopt($ch, CURLOPT_PROXY, $conf['proxy_server'] .':' .$conf['proxy_port']);
      curl_setopt($ch, CURLOPT_PROXYTYPE, 'HTTP');
    }
    curl_setopt($ch, CURLOPT_HEADER, FALSE);
    curl_setopt($ch, CURLOPT_WRITEFUNCTION, 'acquia_remote_file_curl_write');
    // Causes a warning if PHP safe mode is on.
    @curl_setopt($ch, CURLOPT_FOLLOWLOCATION, TRUE);
    $transfer_success = curl_exec($ch);
    curl_close($ch);
  }

  if ($transfer_success && $file = acquia_save_file($filepath, $settings['permanent'], $settings['upload_validators'], $settings['upload_location'])) {
    // Delete the temporary file.
    @unlink($filepath);
    return $file;
  }
  @unlink($filepath);
  return FALSE;
}

/**
 * Set a transfer key that can be retreived by the progress function.
 */
function acquia_remote_file_set_transfer_options($options = NULL) {
  static $current = FALSE;
  if (isset($options)) {
    $current = $options;
  }
  return $current;
}

/**
 * Save a file into the database after validating it.
 *
 * This function is identical to the core function file_save_upload() except
 * that it accepts an input file path instead of an input file source name.
 *
 * @see file_save_upload().
 */
function acquia_save_file($filepath, $permanent =0, $validators = array(), $destination = FALSE, $replace = FILE_EXISTS_RENAME) {
  global $user;

  // Begin building file object.
  $file = new stdClass();
  $file->uid      = $user->uid;
  $file->filename = trim(basename($filepath), '.');
  $file->uri      = $filepath;
  $file->filemime = file_get_mimetype($file->filename);
  $file->filesize = filesize($filepath);
  // Change the status
  $file->status = 1;

  $extensions = '';
  if (isset($validators['file_validate_extensions'])) {
    if (isset($validators['file_validate_extensions'][0])) {
      // Build the list of non-munged extensions if the caller provided them.
      $extensions = $validators['file_validate_extensions'][0];
    }
    else {
      // If 'file_validate_extensions' is set and the list is empty then the
      // caller wants to allow any extension. In this case we have to remove the
      // validator or else it will reject all extensions.
      unset($validators['file_validate_extensions']);
    }
  }
  else {
    // No validator was provided, so add one using the default list.
    // Build a default non-munged safe list for file_munge_filename().
    $extensions = 'jpg jpeg gif png txt doc xls pdf ppt pps odt ods odp json';
    $validators['file_validate_extensions'] = array();
    $validators['file_validate_extensions'][0] = $extensions;
  }

  if (!empty($extensions)) {
    // Munge the filename to protect against possible malicious extension hiding
    // within an unknown file type (ie: filename.html.foo).
    $file->filename = file_munge_filename($file->filename, $extensions);
  }

  // Rename potentially executable files, to help prevent exploits (i.e. will
  // rename filename.php.foo and filename.php to filename.php.foo.txt and
  // filename.php.txt, respectively). Don't rename if 'allow_insecure_uploads'
  // evaluates to TRUE.
  if (!variable_get('allow_insecure_uploads', 0) && preg_match('/\.(php|pl|py|cgi|asp|js)(\.|$)/i', $file->filename) && (substr($file->filename, -4) != '.txt')) {
    $file->filemime = 'text/plain';
    $file->uri .= '.txt';
    $file->filename .= '.txt';
    // The .txt extension may not be in the allowed list of extensions. We have
    // to add it here or else the file upload will fail.
    if (!empty($extensions)) {
      $validators['file_validate_extensions'][0] .= ' txt';
      drupal_set_message(t('For security reasons, your upload has been renamed to %filename.', array('%filename' => $file->filename)));
    }
  }

  // If the destination is not provided, use the temporary directory.
  if (empty($destination)) {
    $destination = 'temporary://';
  }

  // Assert that the destination contains a valid stream.
  $destination_scheme = file_uri_scheme($destination);
  if (!$destination_scheme || !file_stream_wrapper_valid_scheme($destination_scheme)) {
    drupal_set_message(t('The file could not be uploaded, because the destination %destination is invalid.', array('%destination' => $destination)), 'error');
    return FALSE;
  }

  // A URI may already have a trailing slash or look like "public://".
  if (substr($destination, -1) != '/') {
    $destination .= '/';
  }

  // Ensure the destination is writable.
  file_prepare_directory($destination, FILE_CREATE_DIRECTORY);

  $file->destination = file_destination($destination . $file->filename, $replace);
  // If file_destination() returns FALSE then $replace == FILE_EXISTS_ERROR and
  // there's an existing file so we need to bail.
  if ($file->destination === FALSE) {
    drupal_set_message(t('The file %source could not be uploaded because a file by that name already exists in the destination %directory.', array('%source' => $file->filename, '%directory' => $destination)), 'error');
    return FALSE;
  }

  // Add in our check of the the file name length.
  $validators['file_validate_name_length'] = array();

  // Call the validation functions specified by this function's caller.
  $errors = file_validate($file, $validators);

  // Check for errors.
  if (!empty($errors)) {
    $message = t('The specified file %name could not be uploaded.', array('%name' => $file->filename));
    if (count($errors) > 1) {
      $message .= theme('item_list', array('items' => $errors));
    }
    else {
      $message .= ' ' . array_pop($errors);
    }
    drupal_set_message($message, 'error');
    return FALSE;
  }

  // Move uploaded files from PHP's upload_tmp_dir to Drupal's temporary
  // directory. This overcomes open_basedir restrictions for future file
  // operations.
  $file->uri = $file->destination;
  if (!file_unmanaged_copy($filepath, $file->uri, $replace)) {
    drupal_set_message(t('File upload error. Could not move uploaded file.'), 'error');
    watchdog('file', 'Upload error. Could not move uploaded file %file to destination %destination.', array('%file' => $file->filename, '%destination' => $file->uri));
    return FALSE;
  }

  // Set the permissions on the new file.
  drupal_chmod($file->uri);

  // If we are replacing an existing file re-use its database record.
  if ($replace == FILE_EXISTS_REPLACE) {
    $existing_files = file_load_multiple(array(), array('uri' => $file->uri));
    if (count($existing_files)) {
      $existing = reset($existing_files);
      $file->fid = $existing->fid;
    }
  }

  // If we made it this far it's safe to record this file in the database.
  return file_save($file);
}

/**
 * cURL write function to save the file to disk. Also updates progress bar.
 */
function acquia_remote_file_curl_write(&$ch, $data) {
  $progress_update = 0;
  $options = acquia_remote_file_set_transfer_options();

  // Get the current progress and update the progress value.
  // Only update every 64KB to reduce cache_set calls. cURL usually writes
  // in 16KB chunks.
  if (curl_getinfo($ch, CURLINFO_SIZE_DOWNLOAD) / 65536 > $progress_update) {
    $progress_update++;
    $progress = array(
      'current' => curl_getinfo($ch, CURLINFO_SIZE_DOWNLOAD),
      'total' => curl_getinfo($ch, CURLINFO_CONTENT_LENGTH_DOWNLOAD),
    );
    // Set a cache so that we can retrieve this value from the progress bar.
    $cid = 'filefield_transfer:'. session_id() . ':' . $options['key'];
    if ($progress['current'] != $progress['total']) {
      cache_set($cid, $progress, 'cache', time() + 300);
    }
    else {
      cache_clear_all($cid, 'cache');
    }
  }

  $data_length = 0;
  if ($fp = @fopen($options['filepath'], 'a')) {
    fwrite($fp, $data);
    fclose($fp);
    $data_length = strlen($data);
  }

  return $data_length;
}

/**
 * Parse cURL header and record the filename specified in Content-Disposition.
 */
function _acquia_remote_file_parse_header(&$ch, $header) {
  if (preg_match('/Content-Disposition:.*?filename="(.+?)"/', $header, $matches)) {
    // Content-Disposition: attachment; filename="FILE NAME HERE"
    _acquia_remote_file_filename($matches[1]);
  }
  elseif (preg_match('/Content-Disposition:.*?filename=([^; ]+)/', $header, $matches)) {
    // Content-Disposition: attachment; filename=file.ext
    $uri = trim($matches[1]);
    _acquia_remote_file_filename($uri);
  }
  elseif (preg_match('/Content-Type:[ ]*([a-z0-9_\-]+\/[a-z0-9_\-]+)/i', $header, $matches)) {
    $mime_type = $matches[1];
    _acquia_remote_file_mime_extension($mime_type);
  }

  // This is required by cURL.
  return strlen($header);
}

/**
 * Get/set the remote file name in a static variable.
 */
function _acquia_remote_file_filename($curl_filename = NULL) {
  static $filename = NULL;
  if (isset($curl_filename)) {
    $filename = $curl_filename;
  }
  return $filename;
}

/**
 * Get/set the remote file extension in a static variable.
 */
function _acquia_remote_file_mime_extension($curl_mime_type = NULL) {
  static $extension = NULL;
  if (isset($curl_mime_type)) {
    include_once DRUPAL_ROOT . '/includes/file.mimetypes.inc';
    $curl_mime_type = drupal_strtolower($curl_mime_type);
    $mapping = file_mimetype_mapping();
    // See if this matches a known MIME type.
    $map_id = array_search($curl_mime_type, $mapping['mimetypes']);
    if ($map_id !== FALSE) {
      // If we have a match, get this list of likely extensions. For some reason
      // Drupal lists the "most common" extension last for most file types
      // including php, jpg, and doc.
      if ($extensions = array_keys($mapping['extensions'], $map_id)) {
        $extension = end($extensions);
      }
    }
  }
  return $extension;
}
/**
 * Clean up the file name, munging extensions and transliterating.
 *
 * @param $filepath
 *   A string containing a file name or full path. Only the file name will
 *   actually be modified.
 * @return
 *   A file path with a cleaned-up file name.
 */
function acquia_file_clean_filename($filepath, $extensions) {
  global $user;

  $filename = basename($filepath);

  if (module_exists('transliteration')) {
    module_load_include('inc', 'transliteration');

    $langcode = NULL;
    if (!empty($_POST['language'])) {
      $languages = language_list();
      $langcode = isset($languages[$_POST['language']]) ? $_POST['language'] : NULL;
    }
    $filename = transliteration_clean_filename($filename, $langcode);
  }

  // Because this transfer mechanism does not use file_save_upload(), we need
  // to manually munge the filename to prevent dangerous extensions.
  // See file_save_upload().
  if (empty($extensions)) {
    $extensions = 'jpg jpeg gif png txt doc xls pdf ppt pps odt ods odp';
  }
  $filename = file_munge_filename($filename, $extensions);
  $directory = drupal_dirname($filepath);
  return ($directory != '.' ? $directory . '/' : '') . $filename;
}
