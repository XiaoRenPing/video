<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>视频浏览</title>
  <script type="text/javascript">


		function snapshot() {
			var obj = new ActiveXObject("IMAGE");
			var result = obj.readImageFile(1);
			alert(result);
		}
	</script>
</head>
<body>
	<button class="stop" type="button" onclick="snapshot();">截图</button>
</body>
</html>