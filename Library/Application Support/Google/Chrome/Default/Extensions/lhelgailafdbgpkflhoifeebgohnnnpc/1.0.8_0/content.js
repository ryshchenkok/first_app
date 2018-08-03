var version = chrome.runtime.getManifest().version;
var isNewNm;

if (document.getElementById('websigner-sign-plugin-detector')) {
    document.getElementById('websigner-sign-plugin-detector').innerHTML = version;
}

if (document.getElementById('ibank-sign-plugin-detector')) {
    document.getElementById('ibank-sign-plugin-detector').innerHTML = version;
}

var Base64 = {
    _keyStr: "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=",
    encode: function (e) {
        if (typeof e !== 'string') {
            e = JSON.stringify(e);
        }
        var t = "";
        var n, r, i, s, o, u, a;
        var f = 0;
        e = Base64._utf8_encode(e);
        while (f < e.length) {
            n = e.charCodeAt(f++);
            r = e.charCodeAt(f++);
            i = e.charCodeAt(f++);
            s = n >> 2;
            o = (n & 3) << 4 | r >> 4;
            u = (r & 15) << 2 | i >> 6;
            a = i & 63;
            if (isNaN(r)) {
                u = a = 64
            } else if (isNaN(i)) {
                a = 64
            }
            t = t + this._keyStr.charAt(s) + this._keyStr.charAt(o) + this._keyStr.charAt(u) + this._keyStr.charAt(a);
        }
        return t;
    },
    _utf8_encode: function (e) {
        e = e.replace(/\r\n/g, "\n");
        var t = "";
        for (var n = 0; n < e.length; n++) {
            var r = e.charCodeAt(n);
            if (r < 128) {
                t += String.fromCharCode(r)
            } else if (r > 127 && r < 2048) {
                t += String.fromCharCode(r >> 6 | 192);
                t += String.fromCharCode(r & 63 | 128);
            } else {
                t += String.fromCharCode(r >> 12 | 224);
                t += String.fromCharCode(r >> 6 & 63 | 128);
                t += String.fromCharCode(r & 63 | 128);
            }
        }
        return t;
    }
};

window.addEventListener("message", function (event) {
    if (event.source === window && event.data.sender === "ibank.plugin.js") {
        var command = JSON.parse(document.getElementById("iBankSignPluginInstance").value);
        command.url = document.URL;
        event.data.request = Base64.encode(JSON.stringify(command));
        document.getElementById("iBankSignPluginInstance").value = "";
        chrome.extension.sendMessage(event.data, null);
    } else if (event.source === window && event.data.sender === "websigner.plugin.js") {
        isNewNm = true;
        chrome.runtime.sendMessage(event.data, null);
    }
}, false);

chrome.extension.onMessage.addListener(function (request) {
    if (isNewNm) {
        request.sender = "websigner.plugin.native";
    } else {
        request.sender = "ibank.plugin.native";
    }
    window.postMessage(request, "*");
});