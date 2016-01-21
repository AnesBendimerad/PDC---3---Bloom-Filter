<!DOCTYPE>

<html >
  <head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <title>Documents Checker</title>
     
    <link rel="stylesheet" type="text/css" href="/bloom/css/style.css">
	<script type='text/javascript' src="js/prefixfree.min.js"></script>
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.1/jquery.min.js"></script>

	<script type="text/javascript">

	function reinitAjaxCall(){
		
	$.ajax({
		type: "post",
		url: "http://localhost/bloom/index.php/reinitController",
		dataType: "json",
		data: {command_reinit : $('textarea#command_reinit').val() },
		cache: false,
		success: function(data){						
		try{		
			$('#response_reinit').html(data.response);
			$('#others_reinit').html(data.others);
			
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

	function testAjaxCall(){
		
	$.ajax({
		type: "post",
		url: "http://localhost/bloom/index.php/testController",
		dataType: "json",
		data: {config : $('input[name="config"]:checked').val(), command_test : $('textarea#command_test').val() },
		cache: false,
		success: function(data){						
		try{		
			$('#response_test').html(data.response);
			$('#others_test').html(data.others);
			
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

	function statsAjaxCall(){
		
	$.ajax({
		type: "post",
		url: "http://localhost/bloom/index.php/statsController",
		dataType: "json",
		cache: false,
		success: function(data){						
		try{		
			$('#response_stats').html(data.response);
			$('#others_stats').html(data.others);
			
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

	function commandLineAjaxCall(){
		
		var data = $('textarea#command_line').val().split("\n");
		$('#response_command_line').html("");	
		for (var i = 0; i < data.length; ++i) {
			
			if(data[i]){
				
				$.ajax({
				type: "post",
				url: "http://localhost/bloom/index.php/commandLineController",
				dataType: "json",
				async: false,
				data: { command_line : data[i]},
				cache: false,
				success: function(response){						
					try{		
						$('#response_command_line').append("# "+response.response+"<br> <br>");				
					}catch(e) {		
						alert('Exception while request :' + e.message);
					}		
				},
				error: function(){
					alert("Unknown error : please check that the server is runing !");			
				}
				});	
			}
		}
           	return false;
		
}
</script>


<script type="text/javascript">

	function generateAjaxCall(){
		
		$.ajax({
		type: "post",
		url: "http://localhost/bloom/index.php/generateController",
		dataType: "json",
		data: {command_generate : $('textarea#command_generate').val() },
		cache: false,
		success: function(data){						
		try{		
			$('#response_generate').html(data.response);
			$('#others_generate').html(data.others);
			
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
  <label for="tab1">Reinit</label>
   
  <input id="tab2" type="radio" name="tabs">
  <label for="tab2">Generate</label>
  
  <input id="tab3" type="radio" name="tabs">
  <label for="tab3">Test</label>
  
  <input id="tab4" type="radio" name="tabs">
  <label for="tab4">Stats</label>
 
   <input id="tab5" type="radio" name="tabs">
  <label for="tab5">Command line</label>
  
  <section id="content1">
						<center>
							<form id="form1" name="Config_data" method="post" action="">
							<div class="send_container">                                
                                    <textarea rows="1" name="command_reinit" id="command_reinit" cols="70" class="txt_message" placeholder="Please enter the bloom filter size and the hash functions number..."></textarea>
								</div>
                                <input class="button" type="button" name="reinit_submit" onclick="javascript:reinitAjaxCall();" class="send_btn" value="Re-init"/>       
						

						</form>
						</center>
							
							<h1 class="result"> Results</h1><hr/> 
							<div id="bodydesc" style="width:800px; height: 70px; overflow-y: scroll;">
                             <p id="response_reinit" style="font-size: 18px; font-style: normal; color: #777;"> </p>
							<BR> &nbsp; <BR>
							</div>
							
							<h1 class="result"> Others</h1><hr/> 	
							<p id="others_reinit" style="font-size: 18px; font-style: normal;  color: #777;"> </p>
							<BR> &nbsp; <BR>
   
  </section>
  
  
    <section id="content2">
						<center>
							<form id="form2" name="Config_data" method="post" action="">
							<div class="send_container">                                
                                    <textarea rows="1" name="command_generate" id="command_generate" cols="90" class="txt_message" placeholder="Please enter the test file size and the valid documents pourcentage and the test file path"></textarea>
								</div>
                                <input class="button" type="button" name="generate_submit" onclick="javascript:generateAjaxCall();" class="send_btn" value="Generate"/>       
						

						</form>
						</center>
							
							<h1 class="result"> Results</h1><hr/> 
							<div id="bodydesc" style="width:800px; height: 70px; overflow-y: scroll;">
                             <p id="response_generate" style="font-size: 18px; font-style: normal; color: #777;"> </p>
							<BR> &nbsp; <BR>
							</div>
							
							<h1 class="result"> Others</h1><hr/> 	
							<p id="others_generate" style="font-size: 18px; font-style: normal;  color: #777;"> </p>
							<BR> &nbsp; <BR>
   
  </section>
  
  
 <section id="content3">
						<center>
							<form id="form3" name="Config_data" method="post" action="">
							<div class="send_container">                                
                                    <textarea rows="1" name="command_test" id="command_test" cols="75" class="txt_message" placeholder="Please enter the test file path"></textarea>
							</div>
							<BR> &nbsp; <BR>
							<input class="radioButton" type="radio" name="config" id="config" value="0" checked="checked">Bloom and DB verification
							<input class="radioButton" type="radio" name="config" id="config" value="1">Bloom verification
							<input class="radioButton" type="radio" name="config" id="config" value="2">DB verification
							<BR> &nbsp; <BR>
							
                                <input class="button" type="button" name="test_submit" onclick="javascript:testAjaxCall();" class="send_btn" value="Test"/>       
							</form>
						</center>
						
							<h1 class="result"> Results</h1><hr/> 
							<div id="bodydesc" style="width:800px; height: 150px; overflow-y: scroll;">
                             <p id="response_test" style="font-size: 18px; font-style: normal;  color: #777;"> </p>
							<BR> &nbsp; <BR>
							</div>
							<h1 class="result"> Others</h1><hr/> 	
							<p id="others_test" style="font-size: 18px; font-style: normal;  color: #777;"> </p>
							<BR> &nbsp; <BR>
   
 </section>

<section id="content4">
						<center>
							<form id="form4" name="Config_data" method="post" action="">
                            <input class="button" type="button" name="stats_submit" onclick="javascript:statsAjaxCall();" class="send_btn" value="Get stats"/>       
						

						</form>
						</center>

							<h1 class="result"> Results</h1><hr/> 
							<div id="bodydesc" style="width:800px; height: 200px; overflow-y: scroll;">
                             <p id="response_stats" style="font-size: 18px; font-style: normal;  color: #777; "> </p>
							<BR> &nbsp; <BR>
							</div>
							
							
							<h1 class="result"> Others</h1><hr/> 	
							<p id="others_stats" style="font-size: 18px; font-style: normal; color: #777; "> </p>
							<BR> &nbsp; <BR>
							
</section>


  <section id="content5">
						<center>
							<form id="form5" name="Config_data" method="post" action="">
							<div class="send_container">                                
                                    <textarea rows="10" name="command_line" id="command_line" cols="90" class="txt_message" placeholder="Enter your command list .."></textarea>
								</div>
                                <input class="button" type="button" name="command_line_submit" onclick="javascript:commandLineAjaxCall();" class="send_btn" value="Evaluate"/>       
						

						</form>
						</center>
							
							<h1 class="result"> Results</h1><hr/> 
							<div id="bodydesc" style="width:800px; height: 800px; overflow-y: scroll;">
                             <p id="response_command_line" style="font-size: 16px; font-style: normal; color: #777;"> </p>
							<BR> &nbsp; <BR>
							</div>
							
  </section>
  
</main>
</body>
</html>
