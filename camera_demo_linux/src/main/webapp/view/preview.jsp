<%@ page language="java" contentType="text/html; charset=UTF-8"  pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>视频预览</title>


<style>
.plugin {
    width: 600px;
    height: 400px;
}
</style>

</head>
<body>
	<div>
    	<div id="divPlugin" class="plugin"></div>
	</div>
	<script src="${pageContext.request.contextPath }/style/js/jquery-1.7.1.min.js"></script>
	<script src="${pageContext.request.contextPath }/style/js/codebase/webVideoCtrl.js"></script>
<script>

$(function () {
    // 检查插件是否已经安装过
    var iRet = WebVideoCtrl.I_CheckPluginInstall();
    if (-1 == iRet) {
        alert("您还未安装过插件，双击开发包目录里的WebComponentsKit.exe安装！");
        return;
    }

    var oPlugin = {
        iWidth: 600,             // plugin width
        iHeight: 400             // plugin height
    };

    var oLiveView = {
        iProtocol: 1,            // protocol 1：http, 2:https
        szIP: "192.168.1.64",    // protocol ip
        szPort: "8000",            // protocol port
        szUsername: "admin",     // device username
        szPassword: "zc123456", // device password
        iStreamType: 1,          // stream 1：main stream  2：sub-stream  3：third stream  4：transcode stream
        iChannelID: 1,           // channel no
        bZeroChannel: false      // zero channel
    };
        
    // 初始化插件参数及插入插件
    WebVideoCtrl.I_InitPlugin(oPlugin.iWidth, oPlugin.iHeight, {
        bWndFull: true,//是否支持单窗口双击全屏，默认支持 true:支持 false:不支持
        iWndowType: 1,
        cbInitPluginComplete: function () {
            WebVideoCtrl.I_InsertOBJECTPlugin("divPlugin");

            // 检查插件是否最新
            if (-1 == WebVideoCtrl.I_CheckPluginVersion()) {
                alert("检测到新的插件版本，双击开发包目录里的WebComponentsKit.exe升级！");
                return;
            }

            // 登录设备
            WebVideoCtrl.I_Login(oLiveView.szIP, oLiveView.iProtocol, oLiveView.szPort, oLiveView.szUsername, oLiveView.szPassword, {
                success: function (xmlDoc) {
                    // 开始预览
                    var szDeviceIdentify = oLiveView.szIP + "_" + oLiveView.szPort;
                    setTimeout(function () {
                        WebVideoCtrl.I_StartRealPlay(szDeviceIdentify, {
                            iStreamType: oLiveView.iStreamType,
                            iChannelID: oLiveView.iChannelID,
                            bZeroChannel: oLiveView.bZeroChannel
                        });
                    }, 1000);
                }
            });
        }
    });

    // 关闭浏览器
    $(window).unload(function () {
        WebVideoCtrl.I_Stop();
    });
});

</script>
</body>
</html>