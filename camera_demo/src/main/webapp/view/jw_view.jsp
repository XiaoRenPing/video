<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>视频浏览</title>
	<script src="${pageContext.request.contextPath }/style/js/jquery-1.7.1.min.js"></script>
	<script type="text/javascript" src="${pageContext.request.contextPath }/style/js/jwplayer/jwplayer.js"></script>
	<script>jwplayer.key="iP+vLYU9H5KyhZeGt5eVuJJIoULUjltoaMeHXg==";</script>
</head>
<body>
	<div>
		<h3>jwplayer插件</h3>
		<br/>
		<span>先通过java后台获取视频流数据，前端jwplayer插件</span>
		<div id="player">
		Loading...
		</div>
		<div id="scrollDiv" style="width:800px;height:600px;">
			<script type="text/javascript">
				jwplayer("player").setup({
					"file": "rtmp://192.168.1.131/live/",//视频文件路径
					"aspectratio": "16:9",//播放器自适应比例
					"height": "360",//播放器高度
					"repeat":"true",//重复播放（留空则不重复播放）
					"autostart":"true",//自动播放（留空则不启用自动播放）
				});
			</script>
		</div>
		
	</div>
</body>
</html>