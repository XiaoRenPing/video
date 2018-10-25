<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>视频浏览</title>
<link href="/style/js/player/video-js.css" rel="stylesheet" type="text/css">
<script src="/style/js/player/ie8/jquery-1.7.1.min.js"></script>
<script src="/style/js/player/ie8/videojs-ie8.js"></script>
<script src="/style/js/player/video.js"></script>

<script type="text/javascript">
				var devId = 1;
				$(function(){
					$.ajax({
						url:"",
						data:{id:devId},
						async:false,
						success:function(result){
							var data = result.data;
							if(data && data.rtmpUrl){
								var str = "";
							}
						}
					});
				});
			</script>
</head>
<body>
	<div>
		<h3>java输入输出流方式</h3>
		<br/>
		<span>先通过java后台获取视频流数据，再通过整理输出到前端</span>
		<div id="scrollDiv">
			<video id="camera_video" class="video-js vjs-default-skin" controls preload="auto" width="640" height="264" poster="http://vjs.zencdn.net/v/oceans.png" data-setup="{}">
			    <source type="rtmp/flv">
			  <!--   <source src="http://vjs.zencdn.net/v/oceans.mp4" type="video/mp4"> -->
			    <track kind="captions" src="../shared/example-captions.vtt" srclang="en" label="English"></track>
			    <!-- Tracks need an ending tag thanks to IE9 -->
			    <track kind="subtitles" src="../shared/example-captions.vtt" srclang="en" label="English"></track>
			    <p class="vjs-no-js">To view this video please enable JavaScript, and consider upgrading to a web browser that <a href="http://videojs.com/html5-video-support/" target="_blank">supports HTML5 video</a></p>
			</video>
		</div>
	</div>
</body>
</html>