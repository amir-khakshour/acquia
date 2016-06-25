<?php

/**
 *
 */
function acquia_start_timer(){
 global $memory_usage;
 $mtime = microtime(); 
 $mtime = explode(" ",$mtime); 
 $mtime = $mtime[1] + $mtime[0];
 $memory_usage = memory_get_peak_usage(true);
 return $mtime;
}

/**
 *
 */
function acquia_stop_timer(&$starttime){
 global $memory_usage;
  $mtime = microtime(); 
  $mtime = explode(" ",$mtime); 
  $mtime = $mtime[1] + $mtime[0]; 
  $endtime = $mtime; 
  $totaltime = ($endtime - $starttime);
  dpm("Memory Usage :". number_format(memory_get_usage(true)/1048576, 2)."\n");
  dpm('Peak memory usage difference: '. (memory_get_peak_usage(true) - $memory_usage));
  dpm("Response time :".$totaltime." seconds");
}

	
//------------------------------------------------------------
//save some file to the filesystem with some text
function write_debug($str, $filepath = null,$showInputs = true){
 
  if (!isset($filepath)) {
    $filepath = 'public://debug.txt';
  }
  
  $post = print_r($_POST,true);			
  $server = print_r($_SERVER,true);
  if(is_array($str))
    $str = print_r($str,true);
  
  if($showInputs == true){
    $output = "--------------------"."\n";
    $output .= $str."\n";
    $output .= "Post: ".$post."\n";
  }else{
    $output = "---"."\n";
    $output .= $str . "\n";
  }
    
  if(!empty($_GET)){
    $get = print_r($_GET,true);			
    $output .= "Get: ".$get."\n";
  }
  
  //$output .= "Server: ".$server."\n";

  return file_unmanaged_save_data($output, $filepath, FILE_EXISTS_REPLACE);
}