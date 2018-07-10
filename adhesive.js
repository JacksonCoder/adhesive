// adhesive.js
var exec = require('child_process').exec;

function execute(command, callback) {
    exec(command, function(error, stdout, stderr) {
        callback(stdout);
    });
}

module.exports.call = function(func, lang, target, callback) {
    //verify func lang and target are strings
    if (typeof(func) != "string" || typeof(lang) != "string" || typeof(target) != "string") {
        return;
    }
    execute("./adhesive call " + func + " " + lang + " " + target, function(ret_value) {
        callback(ret_value.match(/_ADHESIVERETURN:\({\[(.+)\]}\)/)[1]);
    })
}

module.exports.call("thing", "cpp", "test", function(thing) {
    console.log(thing);
});

module.exports.call("other_thing", "python", "test", function(thing) {
    console.log(thing);
});
