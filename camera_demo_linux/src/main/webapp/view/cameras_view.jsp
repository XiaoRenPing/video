<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="en" xml:lang="en">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>视频浏览</title>
  	
</head>
<body>
	<script type="text/javascript" src="${pageContext.request.contextPath }/style/js/swf/swfobject.js"></script>
	<script type="text/javascript" src="${pageContext.request.contextPath }/style/js/swf/ParsedQueryString.js"></script>
	<script type="text/javascript">
			var player = null;
			
			function loadStream(url) {
			  player.setMediaResourceURL(url);
			}
			
			/* function getlink(url) {
			  return "${pageContext.request.contextPath }/view/camera_view.jsp?src=" + encodeURIComponent(url);
			} */
			
			function jsbridge(playerId, event, data) {
			  if (player == null) {
				player = document.getElementById(playerId);
			  }
			  switch(event) {
				case "onJavaScriptBridgeCreated":
				  listStreams(teststreams,"streamlist");
				  break;
				 case "timeChange":
				 case "timeupdate":
				 case "progress":
				   break;
				 default:
				  console.log(event, data);
				}
			}
			
				// Collect query parameters in an object that we can
				// forward to SWFObject:
			
				var pqs = new ParsedQueryString();
				var parameterNames = pqs.params(false);
				var parameters = {
				    src: "rtmp://192.168.1.131/live/",
					autoPlay: "true",
					verbose: true,
					controlBarAutoHide: "true",
					controlBarPosition: "bottom",
					poster: "images/poster.png",
					javascriptCallbackFunction: "jsbridge",
					plugin_hls: "${pageContext.request.contextPath }/style/js/swf/flashlsOSMF.swf",
					hls_minbufferlength: -1,
					hls_maxbufferlength: 30,
					hls_lowbufferlength: 3,
					hls_seekmode: "KEYFRAME",
					hls_startfromlevel: -1,
					hls_seekfromlevel: -1,
					hls_live_flushurlcache: false,
					hls_info: true,
					hls_debug: false,
					hls_debug2: false,
					hls_warn: true,
					hls_error: true,
					hls_fragmentloadmaxretry : -1,
					hls_manifestloadmaxretry : -1,
					hls_capleveltostage : false,
					hls_maxlevelcappingmode : "downscale"
				};
			
				for (var i = 0; i < parameterNames.length; i++) {
					var parameterName = parameterNames[i];
					parameters[parameterName] = pqs.param(parameterName) ||
					parameters[parameterName];
				}
			
				var wmodeValue = "direct";
				var wmodeOptions = ["direct", "opaque", "transparent", "window"];
				if (parameters.hasOwnProperty("wmode"))
				{
					if (wmodeOptions.indexOf(parameters.wmode) >= 0)
					{
						wmodeValue = parameters.wmode;
					}
					delete parameters.wmode;
				}
				// Embed the player SWF:
				swfobject.embedSWF("${pageContext.request.contextPath }/style/js/swf/GrindPlayer.swf", 
						"GrindPlayer", 
						640, 480, 
						"10.1.0", 
						"expressInstall.swf", 
						parameters, 
						{
							allowFullScreen: "true",
							wmode: wmodeValue
						}, {
							name: "GrindPlayer"
						}
				);
			
			</script>
			
	<div>
		<h3>java输入输出流方式</h3>
		<br/>
		<span>先通过java后台获取视频流数据，再通过整理输出到前端</span>
		
		<div id="scrollDiv">
			<div id="GrindPlayer"></div>
			<!-- <br>
				<input id="userInput" value="rtmp://192.168.1.131/live/" size="80"> 
				<button onclick="userSubmit()">预览流</button><br>
			<p> -->
			<!-- <script type="text/javascript">
				function userSubmit() {
				  window.location = getlink(document.getElementById('userInput').value);
				}
			</script> -->
		</div>
	</div>
	
	<div>
		<a href="${pageContext.request.contextPath }/dev/takephoto?chanel=1">拍照/截图</a>
		<hr/>
		<h3>拍照列表</h3>
		<table>
			<tr>
				<td>序号</td>
				<td>名称</td>
				<td>时间</td>
				<td>操作</td>
			</tr>
			<tr>
				<td>1</td>
				<td>pic1</td>
				<td>2018-10-10</td>
				<td><a href="">预览</a>&nbsp;&nbsp;<a href="">下载</a></td>
			</tr>
			<tr>
				<td>2</td>
				<td>pic2</td>
				<td>2018-01-10</td>
				<td><a href="">预览</a>&nbsp;&nbsp;<a href="">下载</a></td>
			</tr>
		</table>
	</div>
	<div>
		<a href="">录像</a>
		<hr/>
		<h3>录像列表</h3>
		<table>
			<tr>
				<td>序号</td>
				<td>名称</td>
				<td>时长</td>
				<td>操作</td>
			</tr>
			<tr>
				<td>1</td>
				<td>test</td>
				<td>2min</td>
				<td><a href="">播放</a>&nbsp;&nbsp;<a href="">下载</a></td>
			</tr>
			<tr>
				<td>2</td>
				<td>test2</td>
				<td>12min</td>
				<td><a href="">播放</a>&nbsp;&nbsp;<a href="">下载</a></td>
			</tr>
		</table>
	</div>
</body>
</html>