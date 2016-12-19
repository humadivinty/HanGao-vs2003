// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 FOUTHHWYDLL_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// FOUTHHWYDLL_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef FOUTHHWYDLL_EXPORTS
#define FOUTHHWYDLL_API __declspec(dllexport)
#else
#define FOUTHHWYDLL_API __declspec(dllimport)
#endif


typedef int (_stdcall  *CallbackNETStatusFuc  )(char* pszIP);

// 附件2.1：汉高车牌识别器接口标准规范：

// 车牌识别厂家需要根据下面的说明，封装一个动态链接库，命名为“FouthHWYDll.dll”，放在BIN目录内即可测试。

// 1、提供车牌识别设备的IP地址，端口号，超时时间（即指定时间内，没有获取车牌，就回馈无牌）

// 2、函数参考北京汉王的定义，如下：

/* 
(1)、设置监听服务器的端口号

参数：输入，UINT nPort 
说明：服务器端口号，范围为（1000－65535）之间。
无返回值
 */
FOUTHHWYDLL_API void  __stdcall SetServerPort(UINT nPort);

/*
(2)、启动服务
 
无参数
返回值：true 生成服务监听端；
        false不能生成服务监听端
*/
FOUTHHWYDLL_API  BOOL  __stdcall StartServer();

/* 
(3)、模拟触发，给车牌识别设备发送模拟触发指令，抓拍车辆信息

参数：输入，char  *chIP
返回值：true 模拟触发成功;
        false 模拟触发失败 
*/
FOUTHHWYDLL_API BOOL __stdcall Trigger (char  *chIP);

/* 
(4)、网络异常断开提示
注册网络异常回调函数
    
参数：NETStatusFuc
说明：调用者需要在工程中声明下面类型的回调函数
      VB中
      void (CALLBACK  * CallbackNETStatusFuc)( _bstr_t  strIP)
      PB、VC中的回调函数
      void (CALLBACK  * CallbackNETStatusFuc)( char  *chIP)
      回调函数入口参数说明：strIP和chIP（设备IP），表示某个设备网络出现异常
 */
FOUTHHWYDLL_API void __stdcall RegisterNETStatusEvent(CallbackNETStatusFuc NETFuc);

/*
(5)、停止服务器

无参数
返回值：true成功；false 失败 
*/
FOUTHHWYDLL_API BOOL __stdcall StopServer();

/* 
(6)、得到识别结果

参数：lpPlate    输出，包含颜色的车牌照，格式为“颜色车牌”，比如：白皖A1234警
参数：lpTwoImg   输出，280字节的车牌照二值化图片
参数：strIP      输入，车牌识别设备的IP地址
参数：nDelayTime 输入，超时时间，超过此时间，如果没有获取车牌，直接返回无牌，置lpPlate为空或函数返回值为false
返回值：true获取车牌成功，false获取车牌失败
 */
FOUTHHWYDLL_API BOOL __stdcall GetPlateInfo(char* lpPlate,unsigned char* lpTwoImg,char* strIP, int nDelayTime);

       




// 调用流程是：

// (1)、注册回调函数       RegisterNETStatusEvent(CallbackNETStatusFuc NETFuc) 
// (2)、调用一些设置函数   SetServerPort,StartServer
// (3)、发送模拟触发       Trigger
// (4)、开始获取结果       GetPlateInfo
// (5)、退出               StopServer


// 测试工具的使用：

// 1、设置好AutoVehPlate.ini中的IP，端口，超时等待时间

// 2、打开测试工具

// 3、初始化

// 4、获取识别结果，如果显示“WP”，表示无牌，或获取车牌失败。
