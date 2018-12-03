
	//  模仿json数据  	
	  var jsonList = {
	   "一院":[
	      {"id":"101","name":"101课程"},
	      {"id":"102","name":"102课程"},
	      {"id":"103","name":"103课程"},
	       {"id":"104","name":"104课程"},
	        {"id":"105","name":"105课程"}
	       ],
	       
	   "二院":[
	      {"id":"201","name":"201课程"},
	      {"id":"202","name":"202课程"},
	      {"id":"203","name":"203课程"},
	       {"id":"204","name":"204课程"}
	      ],
	   "三院":[
	   {"id":"301","name":"301课程"},
	      {"id":"302","name":"302课程"},
	      {"id":"303","name":"303课程"}
	    ],
	  };
	  //  获取有几个院系
//	  var len = 0;
//	  for(var s in jsonList){
//	  	len++;
//	     alert(s)
//	  }
	    var flag = false;
	    var $show_register = $("#show_register");
       //  var $box1 = $("#box1");
         var box1 = document.getElementById("box1");
         var register = document.getElementById("register");
         var $cancel = $("#cancel");
		var $departments = $("#departments");
		var $professional = $("#professional");
		var i = 0;
	//  判断院系			
		for(var s in jsonList){
			  var $option = $('<option value='+ (i++) +'>'+ s +'</option>');
			  $departments.append($option);
			 
		}
             var $option = $('<option value='+ (i++) +'>'+ '非本院系' +'</option>');
			  $departments.append($option);
//  判断专业
      $departments.change(function(){
      //	alert($(this).val());
       $("#student_id_input").removeAttr("disabled");
	   $("#name_input").removeAttr("disabled");
      	 $professional.html("");
        if($(this).val() == 0){
        	 $professional.append();
          		for(var i = 0;i<jsonList.一院.length;i++){
		              var $option = $('<option>'+ jsonList.一院[i].name +'</option>');
			            $professional.append($option);
	              }
          }	
       
	      if($(this).val() == 1){
	      	 $professional.append();
	      	for(var i = 0;i<jsonList.二院.length;i++){
		              var $option = $('<option>'+ jsonList.二院[i].name +'</option>');
			            $professional.append($option);
	      	   }	      	
	      }
	       
	     if($(this).val() == 2){
	            
	      	for(var i = 0;i<jsonList.三院.length;i++){
		              var $option = $('<option>'+ jsonList.三院[i].name +'</option>');
			            $professional.append($option);
	      	   }
        }
	     
      if($(this).val() == 3){
      	var student_id_input = document.getElementById("student_id_input");
      	var name_input = document.getElementById("name_input");
      	var $option = $('<option>'+ '非本院系' +'</option>');
		$professional.append($option);
		  $("#student_id_input").attr("disabled","disabled");			  
		  $("#name_input").attr("disabled","disabled");
          student_id_input.value = "";
          name_input.value = "";			  
      }
      });

  
//      for(var s in jsonList){
//      	if()
//      }
	
//	for(var i = 0;i<jsonList.一院.length;i++){
//		alert(jsonList.一院[i].name);
//	}
	
$show_register.click(function(){
	box1.style.display = "block";
	register.style.display = "none";
	});
	
	
  $cancel.click(function(){
	register.style.display = "block";
	box1.style.display = "none";
})

//对用户名判断
var username_input = document.getElementById("username_input");
username_input.onblur = function(){	
	//用户名正则，4到16位（字母，数字，下划线，减号）
	var uPattern = /^[a-zA-Z0-9_-]{4,16}$/;
	var username_illegal = document.getElementById("username_illegal");	
	var username_input_val = username_input.value.trim();
	if(!uPattern.test(username_input_val)){
		username_illegal.style.display = "block";
		flag = false;
	}else{
		flag = true;
	}
}
username_input.onfocus = function(){
	username_illegal.style.display = "none";
}

  //对密码判断
var password_input = document.getElementById("password_input");
  password_input.onblur = function(){
  	//只能输入6-20个字母、数字、下划线   
  	var pPattern = /^(\w){6,20}$/;
  	var password_input_val = password_input.value.trim();
  	var password_illegal = document.getElementById("password_illegal");
  	  if(!pPattern.test(password_input_val)){
  	  	password_illegal.style.display = "block";
  	  	flag = false;
  	       }else{
  	       	flag = true;
  	       }
  	   }
  	password_input.onfocus = function(){
  		password_illegal.style.display = "none";
  	}
  	 
  //  两次密码判断	 
var confirm_password_input = document.getElementById("confirm_password_input");
confirm_password_input.onblur = function(){
		var password_input_val = password_input.value.trim();
		var confirm_password_val = confirm_password_input.value.trim();
		var confirm_password_unagree = document.getElementById("confirm_password_unagree");
		if(password_input_val != confirm_password_val){
			confirm_password_unagree.style.display = "block";
			flag = false;
		}else{
			flag = true;
		}
}
confirm_password_input.onfocus = function(){
   	confirm_password_unagree.style.display = "none";
   }
 
 
 //学号
  var student_id_input = document.getElementById("student_id_input");
   student_id_input.onblur = function(){
   	//正整数正则
    var idPattern = /[0-9]{3}$/;
   	var student_id_val = student_id_input.value.trim();
   	var student_id_illegal = document.getElementById("student_id_illegal");
    if(!idPattern.test(student_id_val)){
    	student_id_illegal.style.display = "block";
    	flag = false;
        }else{
        	flag = true;
        }
     }
 	student_id_input.onfocus = function(){
 		student_id_illegal.style.display = "none";
 	}

 var name_input = document.getElementById("name_input");
 name_input.onblur = function(){
 	 var unPattern = /^[\u4E00-\u9FA5A-Za-z]+$/;
 	 var name_input_val = name_input.value.trim();
 	 var name_illegal = document.getElementById("name_illegal");
 	 if(!unPattern.test(name_input_val)){
 	 	name_illegal.style.display = "block";
 	 	flag = false;
 	 }else{
 	 	flag = true;
 	 }
 }
 name_input.onfocus = function(){	
 	name_illegal.style.display = "none";
 }
 
 var submit = document.getElementById("submit");
 
 submit.onclick = function(){
 	
 	var departments = document.getElementById("departments");
 	//   用来判断不是本校的
 	if(flag && departments.value == 3){
 		if((username_input.value.trim() != "") && (password_input.value.trim() != "") &&(confirm_password_input.value.trim() != "")){
 			 alert("可以登入"); 			 
 		}else{
 			alert("有未输入值或输入值不合法");
 		}  //  本校的 
 	} else if(flag && (departments.value != 3) && (username_input.value.trim() != "") && (password_input.value.trim() != "") && (confirm_password_input.value.trim() != "") && (student_id_input.value.trim() != "") && (name_input.value.trim != "")){	
   	alert("可以登入");
    }else{
 			alert("有未输入值或输入值不合法");
 		}
    
    
    
 }
 
 
 
 
  
  //  函数     判断x_illegal.style.display 
//function pattern(x_pattern,x_val,x_illegal){
//	if(!x_pattern.test(x_val)){
//		x_illegal.style.display = "block";
//	}
//}
  	 

