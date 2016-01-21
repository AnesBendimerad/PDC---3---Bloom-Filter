<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');

class commandLineController extends CI_Controller {
	
	function __construct() {
		parent::__construct();
	}

	
	public function index() {
		
		$RESPONSE_END_TAG = "<END/>";
		

	if (isset($_POST['command_line'])) {

		$addr = gethostbyname("localhost");
		$client = stream_socket_client("tcp://$addr:2014", $errno, $errorMessage);

		if ($client === false) {
			throw new UnexpectedValueException("Failed to connect: $errorMessage");
		}
		else{
		    	
			fwrite($client, $_POST['command_line']);
			$server_response = stream_get_line($client,1024,$RESPONSE_END_TAG);
			fclose($client);
			
		    $data = $server_response;
			
			//write to file
			$myfile = fopen("evaluate_output.txt", "a") or die("Unable to open file!");
			fwrite($myfile, $data.PHP_EOL);
			fclose($myfile);
			
			
		   //write on the html page
			header('Content-Type: application/json');
			echo json_encode(array('response' => $server_response));
		}
	}else{
			header('Content-Type: application/json');
			echo json_encode(array('response' => 'Missing parameters : Please fill all the required parameters ! ','others'=> ''));
		}
		
}
}
