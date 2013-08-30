// where http is a module defined in node.js
// common practise to name vars after modules
var http = require("http"); 

function start() {
    function onRequest(request, response) {
        console.log("Request received.");
        response.writeHead(200, {"Content-Type": "text/plain"});
        response.write("Hello World");
        response.end();
    } 
    http.createServer(onRequest).listen(8888);
    console.log("Server started.");
}

// export as a module
// can be invoked as node.js modules
exports.start = start;
