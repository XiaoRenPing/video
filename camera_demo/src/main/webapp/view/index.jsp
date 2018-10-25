<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>视频浏览</title>
<script src="${pageContext.request.contextPath }/style/js/player/ie8/jquery-1.7.1.min.js"></script>
<script src="${pageContext.request.contextPath }/style/js/player/ie8/videojs-ie8.js"></script>

<link href="${pageContext.request.contextPath }/style/css/simpleAlert.css" rel="stylesheet" type="text/css">
<script src="${pageContext.request.contextPath }/style/js/simpleAlert.js"></script>

<script type="text/javascript">
	function takephoto(channel){
		$.get("${pageContext.request.contextPath }/dev/takepic"+channel, function(result){
			var onlyChoseAlert = simpleAlert({
				"content":"<img src=\""+result+""\">",
				"buttons":{"确定":function () {
						onlyChoseAlert.close();
					}
				}
			})
		});
	}
</script>
</head>
<body>
	<div>
		<h3>视频预览</h3>
		<div id="scrollDiv">
			<c:forEach items="${intList }" var="intf">
				<div style="border:1px solid #ff0000;">
					<object type='application/x-vlc-plugin' pluginspage="http://www.videolan.org/" id='vlc' events='false' width="500" height="410">
					    <param name='mrl' value='${intf.viewurl }' /> <%-- rtsp://admin:zc123456@192.168.1.64:554/h264/ch1/main/av_stream --%>
					    <param name='volume' value='50' />
					    <param name='autoplay' value='true' />
					    <param name='loop' value='false' />
					    <param name='fullscreen' value='false' />
					    <param name='controls' value='false' />
					</object>
					<button onclick="javascript:takephoto(${intf.channel});">拍照</button>
				</div>
			</c:forEach>
		</div>
	</div>
</body>
</html>