<!DOCTYPE html>

<html >
  <head>
	<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <title>Documents Checker</title>
	<link rel="stylesheet" type="text/css" href="/bloom/css/style.css">
	<script type='text/javascript' src="js/prefixfree.min.js"></script>
	
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.1/jquery.min.js"></script>

<script type="text/javascript">

	function checkIfExistsAjaxCall(){		
	$.ajax({
		type: "post",
		url: "http://localhost/bloom/index.php/existsController",
		dataType: "json",
		data: {config : $('input[name="config"]:checked').val(), cmd_exists : $('textarea#cmd_exists').val() },
		cache: false,
		success: function(data){						
		try{					
			$('#response_exists').html(data.response);
			$('#others_exists').html(data.others);
			
		}catch(e) {		
			alert('Exception while request :' + e.message);
		}		
		},
		error: function(){			
			alert("Unknown error : please check that the server is runing !");
		}
 });
	return false;
}
</script>

<script type="text/javascript">

	function getDocumentAjaxCall(){
		
	$.ajax({
		type: "post",
		url: "http://localhost/bloom/index.php/getDocumentController",
		dataType: "json",
		data: {cmd_get : $('textarea#cmd_get').val() },
		cache: false,
		success: function(data){						
		try{		
			$('#response_get').html(data.response);
			$('#others_get').html(data.others);
			
		}catch(e) {		
			alert('Exception while request :' + e.message);
		}		
		},
		error: function(){	
			alert("Unknown error : please check that the server is runing !");
		}
 });
	return false;
}

</script>
	
  </head>

  <body>

    <h1>Documents checker</h1>

<main>
  
  <input id="tab1" type="radio" name="tabs" checked>
  <label for="tab1">Exists</label>
    
  <input id="tab2" type="radio" name="tabs">
  <label for="tab2">Get Document</label>
    
  <section id="content1">
                            <center>
							<form id="Config_data" name="Config_data"  action="">
                                <input class="radioButton" type="radio" id="config" name="config"  value="0" checked="checked">Bloom and DB verification
								<input class="radioButton" type="radio" id="config" name="config" value="1">Bloom verification
								<input class="radioButton" type="radio" id="config" name="config" value="2">DB verification
								<BR> &nbsp; <BR>
                                
                                <div class="send_container">                                
                                    <textarea rows="1" name="cmd_exists" id="cmd_exists" cols="70" class="txt_message" placeholder="Please enter a document number..."></textarea>
								</div>
								
								<input name="exists_submit" class="button" type="button" onclick="javascript:checkIfExistsAjaxCall();" class="send_btn" value="Check"/>
                                                              
                            </form>
							</center>
							
							<h1 class="result"> Results</h1><hr/> 
							<div id="bodydesc" style="width:800px; height: 120px; overflow-y: scroll;">							
							<p id="response_exists" style="font-size: 18px; font-style: normal;  color: #777;"> </p>
							<BR> &nbsp; <BR>
							</div>
							
							<h1 class="result"> Others</h1><hr/> 	
							<p id="others_exists" style="font-size: 18px; font-style: normal;  color: #777;"> </p>
							<BR> &nbsp; <BR>
  </section>
    
  <section id="content2">
						<center>
							<form id="Config_data" name="Config_data" method="post" action="">
                                <div class="send_container">                                
                                    <textarea rows="1" name="cmd_get" id="cmd_get" cols="70" class="txt_message" placeholder="Please enter a document number..."></textarea>
								</div>
                                <input class="button"  name="get_submit" type="button" onclick="javascript:getDocumentAjaxCall();" class="send_btn" value="Get"/>       
                        </form>
						</center>
						
						<h1 class="result"> Results</h1><hr/> 	
						<div id="bodydesc" style="width:800px; height: 120px; overflow-y: scroll;">
							<p id="response_get" style="font-size: 18px; font-style: normal;  color: #777;"> </p>
							<BR> &nbsp; <BR>
						</div>
						
							<h1 class="result"> Others</h1><hr/> 	
							<p id="others_get" style="font-size: 18px; font-style: normal;  color: #777;"> </p>
							<BR> &nbsp; <BR>
   
  </section>
</main>
  </body>
</html>
