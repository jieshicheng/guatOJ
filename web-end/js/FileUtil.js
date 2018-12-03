(function(win,undefined){
	 var fso
	try{
		  fso = new ActiveXObject("Scripting.FileSystemObject");
	}catch(e){
		//TODO handle the exception
	}
   
    var file=null;
    var FileUtil=function(){
 
    };
    FileUtil.prototype={
        createTextFile:function(filename){
        	try{
            file=fso.CreateTextFile(filename, true);
            }catch(e){
		//TODO handle the exception
	      }
        },
        write:function(content){
        	try{
            file.WriteLine(content);
             }catch(e){
		//TODO handle the exception
	      }
        },
        closeStream:function(){
            file=null;
        }
    }
    win.FileUtil=FileUtil; 
}(window))