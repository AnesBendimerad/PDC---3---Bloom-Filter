<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');

class reinitController extends CI_Controller {
	
	function __construct() {
		parent::__construct();
	}

	
	public function index() {
		
		$RESPONSE_END_TAG = "<END/>";
		
	if (isset($_POST['command_reinit'])) {

		$addr = gethostbyname("localhost");
		$client = stream_socket_client("tcp://$addr:2014", $errno, $errorMessage);

		if ($client === false) {
			throw new UnexpectedValueException("Failed to connect: $errorMessage");
		}

		fwrite($client, 'reinit '.$_POST['command_reinit']);
		$server_response = stream_get_line($client,1024,$RESPONSE_END_TAG);
		fclose($client);

		
		$response_code = substr($server_response,0,2);
		$server_response = substr($server_response,3,strlen($server_response));
	 
		$msg= '';
		$time= '';
		if($response_code == 'OK'){
		 
			$data = explode(') ',$server_response);
			$msg = 'Successful reset:\n '.str_replace('(', '', $data[0]).'.';
			$time = str_replace(')','',str_replace('(', '', $data[1])).'.';
		}else{
		 
			$msg= 'The following error occurred : '.str_replace(')','',str_replace('(', '', $server_response)).'.';
		}
		
			header('Content-Type: application/json');
			echo json_encode(array('response' => nl2br($msg) , 'others' => $time));
		//echo $msg."</br>".$time;
	}else{
			header('Content-Type: application/json');
			echo json_encode(array('response' => 'Missing parameters : Please fill all the required parameters ! ','others'=> ''));
		}
		
}
}
