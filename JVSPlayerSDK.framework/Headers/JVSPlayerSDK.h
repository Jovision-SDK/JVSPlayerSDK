//
//  JVSPlayerSDK.h
//  JVSPlayerSDK
//
//  Created by Jovision on 2020/7/8.
//  Copyright © 2020 Jovision. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

typedef enum
{
    JVS_NONE = 0,                        /*!< 无状态 */
    JVS_CONNECTED,                       /*!< 已连接 */
    JVS_CONNECT_FAILED,                  /*!< 连接失败 */
    JVS_CONNECTION_LIMIT,                /*!< 连接限制（p2p连接时，设备连接达到上线了） */
    JVS_CONNECTION_BROKEN,               /*!< 连接中断（网络异常或服务中断） */
    JVS_CONNECTION_PLAYBACK_OVER,        /*!< 回放结束 */
    JVS_CONNECTION_DISCONNECTED,        /*!< 连接断开（连接正常结束，录像回放结束） */

    JVS_VIDEO_LOADING,                   /*!< 正在缓冲 */
    JVS_VIDEO_DECODE_FAILED,             /*!< 解码失败 */
    JVS_VIDEO_DECODE_SUCCESS,            /*!< 解码成功，收到解码成功后即可调用show接口来预览图像 */
    JVS_VIDEO_INFO_ENCRYPTION,            /*!< 视频信息，收到此状态表明视频流是加密流 */
    JVS_MAX
}play_state;
typedef enum {
    VideoNormal,      // 未连接状态
    VideoConnect,     //连接
    VideoConnecting,  //已连接
    NewVideoConnected,   //缓冲中
    VideoPlaying,     //播放状态
    VideoFailed       //失败状态
}VideoStatus;
typedef enum
{
    Video_HRS_NONE = 0,                        /*!< 无状态 */
    Video_HRS_START_RECORD,                    /*!< 开始录像 */
    Video_HRS_CREATE_PACKAGE_OK,                /*!< 创建录像文件成功，收到json数据，详见：player_record */
    Video_HRS_CREATE_PACKAGE_FAILED,            /*!< 创建录像文件失败 */
    Video_HRS_CLOSE_PACKAGE_OK,                /*!< 关闭录像文件成功，收到json数据，详见：player_record */
    Video_HRS_CLOSE_PACKAGE_FAILED,            /*!< 关闭录像文件失败 */
    Video_HRS_WRITE_FAILED,                    /*!< 写入失败 */
    Video_HRS_STORE_THE_WARNING,                /*!< 存储空间不足*/
    Video_HRS_STOP_RECORD,                    /*!< 关闭录像 */
    Video_HRS_MAX
}record_state;

/* JPET_INTERCOM 状态定义 */
typedef enum
{
    Chat_NONE = 0,                        /*!< 无状态 */
    Chat_START_OK,                        /*!< 开始对讲成功 */
    Chat_START_FAILED,                    /*!< 开始对讲失败 */
    Chat_BROKEN,                            /*!< 对讲中断 */

    Chat_MAX
}chat_state;
/* JPET_DOWNLOAD 状态定义 */
typedef enum
{
    Down_NONE = 0,                        /*!< 无状态 */
    Down_START_DOWNLOAD_FAILED,            /*!< 开始下载失败 */
    Down_CREATE_PACKAGE_OK,                /*!< 创建录像文件成功，收到json数据，详见：player_download */
    Down_CREATE_PACKAGE_FAILED,            /*!< 创建下载文件失败 */
    Down_CLOSE_PACKAGE_OK,                /*!< 关闭下载文件成功，收到json数据，详见：player_download */
    Down_WRITE_FAILED,                    /*!< 写入失败 */
    Down_STORE_THE_WARNING,                /*!< 存储空间不足*/
    Down_DOWNLOAD_OVER,                    /*!< 下载完成 */
    Down_PLAY_DOWNLOAD_POS,                /*!< 下载录像进度，详见json定义，method：player_download_pos */

    Down_MAX
}Download_state_e;
typedef enum{
    
    Ap_NONE = 0,                        /*!< 无状态 */
    Ap_CONNECT_FAIL,                    /*!< 连接设备失败 */
    Ap_CONNECT_OVERTIME,                /*!< 无操作超时断开 */
    Ap_GET_WIFI_LIST_OK,                /*!< 获取WIFI列表成功 */
    Ap_GET_WIFI_LIST_FAIL,                /*!< 获取WIFI列表失败 */
    Ap_SET_WIFI_OK,                    /*!< 设置设备WIFI成功 */
    Ap_SET_WIFI_FAIL,                    /*!< 设置设备WIFI失败 */

    Ap_MAX    
}Ap_state_e;
@protocol ConnectDelegate <NSObject>

/// 连接事件状态回调
/// @param channel 通道号
/// @param eventType 事件类型
-(void)ConnectEventCallBackChannel:(int)channel withEventType:(int)eventType;

/// 视频连接状态回调
/// @param channel 通道号
/// @param eventState 事件类型
-(void)VideoEventCallBackChannel:(int)channel withEventState:(int)eventState;

/// 录像回调
/// @param channel          本地通道号
/// @param recordState 录像状态
/// @param recordInfo   录像信息
-(void)RecordVideoEventCallBackChannel:(int)channel withEventState:(int)recordState recordInfo:(NSDictionary *)recordInfo;

/// 对讲状态回调
/// @param channel 本地通道号
/// @param chatState 对讲状态回调
-(void)ChatEventCallBackChannel:(int)channel withEventState:(int)chatState;

@end
@protocol DownDelegate <NSObject>

/// 下载回调
/// @param playerId 下载playerId
/// @param donwState 下载状态
/// @param jsonData 下载回调数据
-(void)downPlayerId:(int)playerId withEventState:(Download_state_e)donwState withJsonData:(NSDictionary *)jsonData;

@end
@protocol PlayBackCallBackDelegate <NSObject>
//实时回放数据
-(void)playBackTimeInfoChannel:(int)nLocalChannel withTimeInfo:(id)timeInfo;

@end
@protocol ApNetDelegate <NSObject>

-(void)apPlayerId:(int)playerId withEventState:(Ap_state_e)apState withJsonData:(NSDictionary *)jsonData;

@end
@interface JVSPlayerSDK : NSObject
@property(nonatomic, weak) id<ConnectDelegate> ConnectDelegate;
@property(nonatomic, weak) id<PlayBackCallBackDelegate> playBackCallBackDelegate;
@property(nonatomic, weak) id<DownDelegate> playerBackDownDelegate;
@property(nonatomic, weak) id<ApNetDelegate> apDelegate;
//获取版本信息
-(NSString *)getVersion;
//销毁网络库
-(void)releasePlayerSDK;

/// 初始化单例
+(instancetype)shareInstanceSDK;

/// 初始化网路库
/// @param logLevel 日志等级  0：无日志，1：有日志，2...其他暂未定义
/// @param logPath   日志本地路径
-(void)initPlayerSDK:(int)logLevel logPath:(NSString *)logPath;

/// 进入前台重置播放库
-(void)resetPlayerForEnterForgroud;

/// 连接设备
/// @param p2pInfo   流信息
/// @param deviceChannel 本地通道号
/// @param remoteChannel 远程通道号（p2p能用到）
/// @param stream 码流（p2p能用到）
/// @param isratio 是否保持原画面比
-(void)deviceConnect:(NSString *)p2pInfo withChannel:(int)deviceChannel withShowVideoView:(UIView *)showVideoView withRemoteChannel:(int)remoteChannel withStream:(int)stream isratio:(BOOL)isratio;
/// 断开视频
/// @param nLocalChannel 本地channel号
-(void)disconnect:(int)nLocalChannel;
/// 控制实况暂停/播放
/// @param nLocalChannel 本地通道号
/// @param isPause 是否暂停
-(void)livePauseChannel:(int)nLocalChannel withPause:(BOOL)isPause;
/// 请求I帧
/// @param nLocalChannel 本地通道号
-(void)requestIFrameChannel:(int)nLocalChannel;

/// 播放回放
/// @param deviceInfo 设备详情
/// @param stream 码流
/// @param remoteChannel 远程通道号
/// @param startTime 开始时间
/// @param endTime 结束时间
/// @param showVideoView 播放窗口
/// @param connectType 连接类型  1.好望。2.国标和云端
-(void)playerBackDeviceInfo:(NSString *)deviceInfo withStream:(int)stream withRemoteChannel:(int)remoteChannel withStartTime:(NSString *)startTime withEndTime:(NSString *)endTime withShowVideoView:(UIView *)showVideoView withConnectType:(NSString *)connectType isratio:(BOOL)isratio;
/// 云存储播放
/// @param p2pInfo 流信息
/// @param deviceChannel 本地通道号
/// @param remoteChannel 远程通道号（p2p能用到）
/// @param stream 码流（p2p能用到）
/// @param isratio 是否保持原画面比
-(void)CloudDeviceConnect:(NSString *)p2pInfo withChannel:(int)deviceChannel withShowVideoView:(UIView *)showVideoView withRemoteChannel:(int)remoteChannel withStream:(int)stream isratio:(BOOL)isratio;
/// 本地回放播放
/// @param deviceInfo 设备详情
/// @param stream 码流
/// @param remoteChannel 远程通道号
/// @param startTime 开始时间
/// @param showVideoView 播放窗口
/// @param localChannel 本地通道号
-(void)localPlayerBackDeviceInfo:(NSString *)deviceInfo withStream:(int)stream withRemoteChannel:(int)remoteChannel withStartTime:(NSString *)startTime withShowVideoView:(UIView *)showVideoView withLocalChannel:(int)localChannel;

/// 是否开启监听
/// @param nLocalChannel 本地通道号
/// @param isOpen 状态 开启 YES  关闭 NO
-(void)playerControlSoundChannel:(int)nLocalChannel withSound:(BOOL)isOpen;

/// 获取视频连接状态
/// @param nLocalChannel 本地通道号
-(VideoStatus)playerConnectStatusChannel:(int)nLocalChannel;

/// 控制回放暂停/播放
/// @param nLocalChannel 本地通道号
/// @param isPause 是否暂停
-(void)playBackPauseChannel:(int)nLocalChannel withPause:(BOOL)isPause;
/// 跳单针
/// @param nLocalChannel 本地通道号
-(void)playBackOneStepChannel:(int)nLocalChannel;
/// 设置回放速度
/// @param nLocalChannel 本地通道号
/// @param speed 速度 取值（-3~0~3）播放速度为：2^speed
-(void)playBackSetSpeedChannel:(int)nLocalChannel withSpeed:(int)speed;
/// 根据时间进行跳转
/// @param nLocalChannel 本地通道号
/// @param time 跳转的时间点
-(void)playBackStepChannel:(int)nLocalChannel withTime:(NSString *)time;

/// 本地录像跳转
/// @param nLocalChannel 本地通道号
/// @param time 时间点（毫秒）
-(void)localPlayBackStepChannel:(int)nLocalChannel withTime:(int)time;
/// 改变画布大小
/// @param channnel 通道号
/// @param frame 大小
-(void)changeOpenGLViewFrameChannel:(int)channnel withFrame:(CGRect)frame;

/// 抓拍
/// @param nLocalChannel 本地通道号
/// @param path 本地路径（全路径）.bmp
/// @param imageType 图片类型  0 bmp 1 jpg   2 PNG 其他类型不支持
-(void)playSnapshotChannel:(int)nLocalChannel withWritePath:(NSString *)path imageType:(int)imageType;

/// 录像开始结束命令
/// @param nLocalChannel 本地通道号
/// @param path 本地路径（全路径）/Document/
/// @param name_prefix 录像名称 例如:creat_time
/// @param isOpen Yes开启、No关闭
-(void)playRecordChannel:(int)nLocalChannel withWritePath:(NSString *)path withNamePrefix:(NSString *)name_prefix withIsOpen:(BOOL)isOpen;

/// 按时间段下载
/// @param p2pInfo 流信息
/// @param remoteChannel 远程通道号（p2p能用到）
/// @param stream 码流（p2p能用到）
/// @param beginTime 开始时间 格式的时间，如：2020-06-27T17:18:00+08:00
/// @param endTime 结束时间 格式的时间，如：2020-06-27T17:18:00+08:00
/// @param fileFormat 文件类型 （目前仅支持 0 mp4）
/// @param savePath 保存路径
/// @param saveFileNamePrefix 录像名为：saveFileNamePrefix_开始时间_结束时间.mp4
/// @return playerid 流id 暂停，继续，停止需要用到此id。
-(int)playerDownloadForTimeStart:(NSString *)p2pInfo withRemoteChannel:(int)remoteChannel withStream:(int)stream withBeginTime:(NSString *)beginTime withEndTime:(NSString *)endTime withFileFormat:(int)fileFormat withSavePath:(NSString *)savePath withSaveFileNamePrefix:(NSString *)saveFileNamePrefix;

/// 按文件下载
/// @param p2pInfo 流信息
/// @param fileName 按文件下载时需传入文件名
/// @param beginTime 开始时间 格式的时间，如：2020-06-27T17:18:00+08:00
/// @param endTime 结束时间 格式的时间，如：2020-06-27T17:18:00+08:00
/// @param fileFormat 文件类型 （目前仅支持 0 mp4）
/// @param savePath 保存路径
/// @param saveFileNamePrefix 录像名为：saveFileNamePrefix_开始时间_结束时间.mp4
/// @return playerid  流id 暂停，继续，停止需要用到此id。
-(int)playerDownloadForFileStart:(NSString *)p2pInfo withFileName:(NSString *)fileName withBeginTime:(NSString *)beginTime withEndTime:(NSString *)endTime withFileFormat:(int)fileFormat withSavePath:(NSString *)savePath withSaveFileNamePrefix:(NSString *)saveFileNamePrefix;

/// 暂停下载
/// @param playerId 流id
-(void)playerDownloadPause:(int)playerId;

/// 继续下载
/// @param playerId 流id
-(void)playerDownloadResume:(int)playerId;

/// 继续下载
/// @param playerId 流id
-(void)playerDownloadStop:(int)playerId;

/// 开始对讲，公有云平台
/// @param nLocalChannel 本地通道号
/// @param channelInfo    对讲信息
/// @return chatid    对讲id
- (int)startTalk:(NSString *)channelInfo nLocalChannel:(int)nLocalChannel;

/// 开启语音对讲，融视云平台
/// @param server 服务器地址，形如：127.0.0.1:15050
/// @param devSN 设备SN
/// @param audioCodec 音频编码类型，字符串，例如："g711a" "g711u"
/// @param audioChannel 音频通道数
/// @param audioSamplingRate 音频采样率
/// @param audioSamplingBits 音频采样位宽
/// @return chatid    对讲id

- (int)startTalk:(NSString *)server devSN:(NSString *)devSN audioCodec:(NSString *)audioCodec audioChannel:(int)audioChannel audioSamplingRate:(int)audioSamplingRate audioSamplingBits:(int)audioSamplingBits;

/// 结束对讲
/// @param chat_id 本地通道号
- (void)stopTalk:(int)chat_id;


/***************************************以下接口为附加功能接口**************************************/

/// 二维码配置网络
/// @param wifiName wifi名称
/// @param wifiPwd  wifi密码
/// @return 二维码图片
-(UIImage*)JVSCreateQR:(NSString*)wifiName wifiPwd:(NSString*)wifiPwd;

/// 二维码配置网络
/// @param wifiName wifi名称
/// @param wifiPwd  wifi密码
/// @return 二维码信息字符串
-(NSString *)JVSCreateQRStr:(NSString*)wifiName wifiPwd:(NSString*)wifiPwd;


/// 声波配置网络
/// @param wifiName wifi名称
/// @param wifiPwd  wifi密码
/// @param count      发送次数
- (void)JVSSendSoundWave:(NSString *)wifiName wifiPwd:(NSString *)wifiPwd count:(int)count;

/// 停止声波配置网络
- (void)JVSStopSendSoundWave;

///开始采集声音到文件（AAC编码格式ADTS文件格式），仅支持手机端，不能与语音对讲功能同时使用
/// @param channels 通道数，目前仅支持1通道
/// @param sample_rate 采样率，支持8000、16000
/// @param sample_bits 采样位宽，支持8、16
/// @param fullname aac文件路径
- (void)playerStartCollectSoundToAACFile:(int)channels sample_rate:(int)sample_rate sample_bits:(int)sample_bits fullname:(NSString *)fullname;

///停止采集声音，结束文件写入
- (void)playerStopCollectSound;

/// 播放aac格式的声音文件（AAC编码格式ADTS文件格式），仅支持手机端，不能与语音对讲功能同时使用
/// @param channels 通道数，目前仅支持1通道
/// @param sample_rate 采样率，支持8000、16000
/// @param sample_bits 采样位宽，支持8、16
/// @param fullname aac文件路径
- (void)playerPlayAACFile:(int)channels sample_rate:(int)sample_rate sample_bits:(int)sample_bits fullname:(NSString *)fullname;

///停止播放aac声音文件
- (void)playerStopPlayAACFile;

/// 图片解密（返回图片数据）
///@param pJav                   需要解密的图片
///@param n_size               n_size
///@param dec_key             key
///@param dec_iv               iv
///@param buf                     解密后的图片数据

- (int)JVSDecDataImage:(unsigned char*)pJav n_size:(int)n_size dec_key:(NSString *)dec_key dec_iv:(NSString *)dec_iv buf:(unsigned char*)buf;

/// 图片解密（返回图片路径）
///@param pJav                   需要解密的图片
///@param dec_key             key
///@param dec_iv               iv
///@param path                    解密后的图片路径

- (int)JVSDecPathImage:(unsigned char*)pJav dec_key:(NSString *)dec_key dec_iv:(NSString *)dec_iv path:(NSString*)path;

/// 获取AP配网wifi信息
/// @param userName 设备连接用户名
/// @param password 设备连接密码
-(void)JVSGetApWifiListUserName:(NSString *)userName withPassword:(NSString *)password;

/// 配置ap
/// @param userName 设备用户名
/// @param password 设备密码
/// @param wifiName wifi名称
/// @param wifiPassword wifi密码
-(void)JVSSetApWifiUserName:(NSString *)userName withPassword:(NSString *)password withWifiName:(NSString *)wifiName withPassword:(NSString *)wifiPassword;
@end
