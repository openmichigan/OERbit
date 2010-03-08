/* 
  Code borrowed from: http://safari.oreilly.com/0596101694

  Wrapper function for constructing a request object.
 Parameters:
  reqType: The HTTP request type, such as GET or POST.
  url: The URL of the server program.
  asynch: Whether to send the request asynchronously or not. 
*/


function httpRequest(reqType,url,asynch){
    //Mozilla-based browsers
    if(window.XMLHttpRequest){
        request = new XMLHttpRequest(  );
    } else if (window.ActiveXObject){
        request=new ActiveXObject("Msxml2.XMLHTTP");
        if (! request){
            request=new ActiveXObject("Microsoft.XMLHTTP");
        }
    }
    //the request could still be null if neither ActiveXObject
    //initialization succeeded
    if(request){
        initReq(reqType,url,asynch);
    } else {
        alert("Your browser does not permit the use of all "+
              "of this application's features!");
    }
}
/* Initialize a request object that is already constructed */
function initReq(reqType,url,bool){
    /* Specify the function that will handle the HTTP response */
    request.onreadystatechange=null; 
    request.open(reqType,url,bool);
    request.send(null);
}

