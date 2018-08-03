var signPluginPort;

function onNativeMessage(message) {
    chrome.tabs.query({}, function (tabs) {
        for (var tab in tabs) {
            chrome.tabs.sendMessage(tabs[tab].id, message);
        }
    });
}

function onDisconnected() {
    if (signPluginPort.name === "websigner.plugin") {
        signPluginPort = chrome.runtime.connectNative("com.bifit.ibanksignplugin");
        signPluginPort.name = "ibank.plugin";
        signPluginPort.onMessage.addListener(onNativeMessage);
        signPluginPort.onDisconnect.addListener(onDisconnected);
    } else {
        signPluginPort = null;
    }

    onNativeMessage({error: "disconnected"});
}

function getPlugin() {
    if (!signPluginPort) {
        signPluginPort = chrome.runtime.connectNative("com.bifit.websigner");
        signPluginPort.name = "websigner.plugin";
        signPluginPort.onMessage.addListener(onNativeMessage);
        signPluginPort.onDisconnect.addListener(onDisconnected);
    }
    return signPluginPort;
}

chrome.extension.onMessage.addListener(function (request, sender, sendResponse) {
    if (request.disconnect) {
        if (signPluginPort) {
            signPluginPort.disconnect();
            signPluginPort = null;
        }
    } else {
        getPlugin().postMessage(request.request);
    }
});

chrome.runtime.onUpdateAvailable.addListener(function(details) {
    chrome.runtime.reload();
});

function injectContent() {
    chrome.tabs.query({}, function (tabs) {
        tabs.forEach(function (tab) {
            chrome.tabs.executeScript(tab.id, {file: "content.js"});
        });
    });
}

function onInstall() {
    injectContent();
}

function onUpdate() {
    injectContent();
}

function getVersion() {
    var details = chrome.app.getDetails();
    return details.version;
}

chrome.runtime.requestUpdateCheck(function(status) {
});

// Check if the version has changed.
var currVersion = getVersion();
var prevVersion = localStorage['version'];
if (currVersion !== prevVersion) {
    // Check if we just installed this extension.
    if (typeof prevVersion === 'undefined') {
        onInstall();
    } else {
        onUpdate();
    }
    localStorage['version'] = currVersion;
}
