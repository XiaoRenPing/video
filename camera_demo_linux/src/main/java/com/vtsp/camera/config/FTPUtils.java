package com.vtsp.camera.config;

import java.io.IOException;
import java.io.InputStream;

import org.apache.commons.lang3.StringUtils;
import org.apache.commons.net.ftp.FTPClient;
import org.apache.commons.net.ftp.FTPReply;

/**
 * FTP上传文件的工具类
 * @Date 2017年01月02日 下午15:30:00
 * @author Administrator
 *
 */
public class FTPUtils {
	
	/**
	 * 向FTP服务器上传文件
	 * @param ftpUrl ftpUrl服务器hostname（IP）
	 * @param ftpPort ftpPort服务器端口
	 * @param userName userName服务器登录名
	 * @param password password服务器登录密码
	 * @param uploadPath 上传到ftp服务器的位置路径
	 * @param fileName 上传的文件名称
	 * @param input 上传的文件输入流
	 * @return boolean 上传成功与否
	 */
	public static boolean ftpUpload(final String ftpUrl, final int ftpPort,final String userName, final String password,final String uploadPath, final String fileName,final InputStream input) {
		boolean uploadResult = false;//上传是否成功
		final FTPClient ftp = new FTPClient();//创建FTP客户端对像
		try {
			int reply;//回复码
			ftp.connect(ftpUrl, ftpPort);//通过ip与端口，连接FTP服务器
			ftp.login(userName, password);//通过用户名与密码登录FTP服务器
			ftp.enterLocalPassiveMode();//每次数据连接之前，ftp client告诉ftp server开通一个端口来传输数据
			ftp.setFileType(FTPClient.BINARY_FILE_TYPE);// 设置FTPClient的传输模式为二进制（默认是ASCII）
			reply = ftp.getReplyCode();//获取回复码
			if (!FTPReply.isPositiveCompletion(reply)) {//判断回复码是否已2开头，以2开头的返回值就会为真
				System.out.println("链接FTP服务器失败:[" + reply + "]");
				System.out.println("ftpUrl:" + ftpUrl + " ftpPort:" + ftpPort+ " userName:" + userName + " password:" + password + " uploadPath:" + uploadPath + " fileName:" + fileName);
				//拼接返回消息
				final StringBuilder sb = new StringBuilder();
				if (ftp.getReplyStrings() != null) {
					for (final String s : ftp.getReplyStrings()) {
						sb.append(s);
					}
				}
				System.out.println(ftp.getReplyString() + " " + sb.toString());
				ftp.disconnect();//销毁连接
			} else {
				if(StringUtils.isNotBlank(uploadPath)){//为空则上传到根目录
					final String[] paths = uploadPath.split("/");
					final StringBuffer sb = new StringBuffer();
					sb.append("/");
					// 循环每级目录
					for (int i = 0; i < paths.length; i++) {
						if (!"".equals(paths[i])) {
							sb.append(paths[i] + "/");
							final String path = sb.toString();//重新拼成目录
							System.out.println(path + "path");
							if (!ftp.changeWorkingDirectory(path)) {//切换工作目录，如果返回false表示该目录不存在，同时检查每级目录是否已经创建
								System.out.println("上传路径不存在。开始创建该路径目录...---第" + i + "次创建---...");
								if (ftp.makeDirectory(path)) {//创建目录
									ftp.changeWorkingDirectory(path);// 切换到新生成的工作目录
									System.out.println("创建目录成功。");
								} else {
									System.out.println("创建目录失败！");
								}
							}
						}
					}
				}
				final boolean result = ftp.storeFile(fileName, input);//上传文件
				if (result) {
					uploadResult = true;
					System.out.println("上传文件到FTP服务器成功。");
				} else {
					System.out.println("上传文件到FTP服务器失败!");
				}
			}
		} catch (final IOException e) {
			e.printStackTrace();
		} finally {
			try {
				 if(input!=null){
				     input.close();//关闭文件流
				 }
				 if(ftp!=null){
				     ftp.logout();//退出FTP服务器
				 }
				 if (ftp.isConnected()) {
					 ftp.disconnect();//销毁FTP服务器连接
				 }
			} catch (final IOException ioe) {
			   ioe.printStackTrace();
			}
		}
		return uploadResult;//返回结果
	}
}
