#include <jni.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <android/log.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

/* 宏定义begin */
//清0宏
#define MEM_ZERO(pDest, destSize) memset(pDest, 0, destSize)

//LOG宏定义
#define LOG_INFO(tag, msg) __android_log_write(ANDROID_LOG_INFO, tag, msg)
#define LOG_DEBUG(tag, msg) __android_log_write(ANDROID_LOG_DEBUG, tag, msg)
#define LOG_WARN(tag, msg) __android_log_write(ANDROID_LOG_WARN, tag, msg)
#define LOG_ERROR(tag, msg) __android_log_write(ANDROID_LOG_ERROR, tag, msg)
/* 宏定义end */

#ifndef _Included_main_activity_UninstalledObserverActivity
#define _Included_main_activity_UninstalledObserverActivity
#ifdef __cplusplus
extern "C" {
#endif

#undef main_activity_UninstalledObserverActivity_MODE_PRIVATE
#define main_activity_UninstalledObserverActivity_MODE_PRIVATE 0L
#undef main_activity_UninstalledObserverActivity_MODE_WORLD_READABLE
#define main_activity_UninstalledObserverActivity_MODE_WORLD_READABLE 1L
#undef main_activity_UninstalledObserverActivity_MODE_WORLD_WRITEABLE
#define main_activity_UninstalledObserverActivity_MODE_WORLD_WRITEABLE 2L
#undef main_activity_UninstalledObserverActivity_MODE_APPEND
#define main_activity_UninstalledObserverActivity_MODE_APPEND 32768L
#undef main_activity_UninstalledObserverActivity_MODE_MULTI_PROCESS
#define main_activity_UninstalledObserverActivity_MODE_MULTI_PROCESS 4L
#undef main_activity_UninstalledObserverActivity_BIND_AUTO_CREATE
#define main_activity_UninstalledObserverActivity_BIND_AUTO_CREATE 1L
#undef main_activity_UninstalledObserverActivity_BIND_DEBUG_UNBIND
#define main_activity_UninstalledObserverActivity_BIND_DEBUG_UNBIND 2L
#undef main_activity_UninstalledObserverActivity_BIND_NOT_FOREGROUND
#define main_activity_UninstalledObserverActivity_BIND_NOT_FOREGROUND 4L
#undef main_activity_UninstalledObserverActivity_BIND_ABOVE_CLIENT
#define main_activity_UninstalledObserverActivity_BIND_ABOVE_CLIENT 8L
#undef main_activity_UninstalledObserverActivity_BIND_ALLOW_OOM_MANAGEMENT
#define main_activity_UninstalledObserverActivity_BIND_ALLOW_OOM_MANAGEMENT 16L
#undef main_activity_UninstalledObserverActivity_BIND_WAIVE_PRIORITY
#define main_activity_UninstalledObserverActivity_BIND_WAIVE_PRIORITY 32L
#undef main_activity_UninstalledObserverActivity_BIND_IMPORTANT
#define main_activity_UninstalledObserverActivity_BIND_IMPORTANT 64L
#undef main_activity_UninstalledObserverActivity_BIND_ADJUST_WITH_ACTIVITY
#define main_activity_UninstalledObserverActivity_BIND_ADJUST_WITH_ACTIVITY 128L
#undef main_activity_UninstalledObserverActivity_CONTEXT_INCLUDE_CODE
#define main_activity_UninstalledObserverActivity_CONTEXT_INCLUDE_CODE 1L
#undef main_activity_UninstalledObserverActivity_CONTEXT_IGNORE_SECURITY
#define main_activity_UninstalledObserverActivity_CONTEXT_IGNORE_SECURITY 2L
#undef main_activity_UninstalledObserverActivity_CONTEXT_RESTRICTED
#define main_activity_UninstalledObserverActivity_CONTEXT_RESTRICTED 4L
#undef main_activity_UninstalledObserverActivity_RESULT_CANCELED
#define main_activity_UninstalledObserverActivity_RESULT_CANCELED 0L
#undef main_activity_UninstalledObserverActivity_RESULT_OK
#define main_activity_UninstalledObserverActivity_RESULT_OK -1L
#undef main_activity_UninstalledObserverActivity_RESULT_FIRST_USER
#define main_activity_UninstalledObserverActivity_RESULT_FIRST_USER 1L
#undef main_activity_UninstalledObserverActivity_DEFAULT_KEYS_DISABLE
#define main_activity_UninstalledObserverActivity_DEFAULT_KEYS_DISABLE 0L
#undef main_activity_UninstalledObserverActivity_DEFAULT_KEYS_DIALER
#define main_activity_UninstalledObserverActivity_DEFAULT_KEYS_DIALER 1L
#undef main_activity_UninstalledObserverActivity_DEFAULT_KEYS_SHORTCUT
#define main_activity_UninstalledObserverActivity_DEFAULT_KEYS_SHORTCUT 2L
#undef main_activity_UninstalledObserverActivity_DEFAULT_KEYS_SEARCH_LOCAL
#define main_activity_UninstalledObserverActivity_DEFAULT_KEYS_SEARCH_LOCAL 3L
#undef main_activity_UninstalledObserverActivity_DEFAULT_KEYS_SEARCH_GLOBAL
#define main_activity_UninstalledObserverActivity_DEFAULT_KEYS_SEARCH_GLOBAL 4L

/*
 * Class:     main_activity_UninstalledObserverActivity
 * Method:    init
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_example_testndk_MainActivity_eventUninstall(JNIEnv *, jobject, jstring, jstring, jint);

#ifdef __cplusplus
}
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* 内全局变量begin */
static char c_TAG[] = "MyActivity.eventUninstall";

static char event_file[] = "/data/data/com.example.testndk/files/observedUninstallFile";
static char event_dir[] = "/data/data/com.example.testndk/files";
static char event_lockFile[] = "/data/data/com.example.testndk/files/lockFile";
static char app_dir[] = "/data/data/com.example.testndk";
static char split[] = "/";
static jboolean b_IS_COPY = JNI_TRUE;
/* 内全局变量 */

/*
 * Class:     main_activity_UninstalledObserverActivity
 * Method:    init
 * Signature: ()V
 */

int check_watch(JNIEnv *env, jstring path){
	int fileDescriptor = inotify_init();
	if (fileDescriptor < 0) {
		LOG_DEBUG(c_TAG, "inotify init failed !!!");
		return 1;
	}

	strcat(event_file, event_dir);

	int watchDescriptor = inotify_add_watch(
			fileDescriptor,
			env->GetStringUTFChars(path, &b_IS_COPY),
			IN_DELETE);
	//event_file
	if (watchDescriptor < 0) {
		LOG_DEBUG(c_TAG, "inotify_add_watch failed !!!");
		return 1;
	}

	void *p_buf = malloc(sizeof(struct inotify_event));
	if (p_buf == NULL) {
		LOG_DEBUG(c_TAG, "malloc failed !!!");
		return 1;
	}

	LOG_INFO(c_TAG, "start observer !!!");

	size_t readBytes = read(fileDescriptor, p_buf, sizeof(struct inotify_event));

	FILE *p_appDir = fopen(env->GetStringUTFChars(path, &b_IS_COPY), "r");
	// 确认已卸载
	if (p_appDir == NULL) {
		LOG_INFO(c_TAG, "uninstall !!!");

		//read 函数会阻塞线程， run here 说明目录被删除，所以在此处释放监听器内存，注销监听器
		free(p_buf);
		inotify_rm_watch(fileDescriptor, IN_DELETE);
	} else {
		int watchDescriptorA = inotify_add_watch(
			fileDescriptor,
			env->GetStringUTFChars(path, &b_IS_COPY),
			IN_DELETE);
		if (watchDescriptorA < 0) {
			LOG_DEBUG(c_TAG, "inotify_add_watch failed !!!");
			return 1;
		}

		size_t readBytesA = read(fileDescriptor, p_buf, sizeof(struct inotify_event));
	}

	return 0;
}

JNIEXPORT void JNICALL Java_com_example_testndk_MainActivity_eventUninstall(JNIEnv *env, jobject obj, jstring path, jstring url, jint version)
{
	char buf[64];
	sprintf(buf, "%d", version);
	jstring version_str = env->NewStringUTF(buf);

	LOG_INFO(c_TAG, "init");

	pid_t pid = fork();

	if (pid < 0) {
		LOG_ERROR(c_TAG, "fork fail!!!");
		exit(1);
	} else if (pid == 0) {

		//监听文件所在文件夹不存在，则创建此文件夹
		FILE *p_filesDir = fopen(event_dir, "r");
		if (p_filesDir == NULL) {
			//int filesDirRet = mkdir(env->GetStringUTFChars(path+"/"+event_dir, NULL), S_IRWXU | S_IRWXG | S_IXOTH);
			int filesDirRet = mkdir(event_dir, S_IRWXU | S_IRWXG | S_IXOTH);
			if (filesDirRet == -1) {
				LOG_ERROR(c_TAG, "make dir fail");
				exit(1);
			}
		}

		//监听文件不存在，则创建文件
		FILE *p_observedUninstallFile = fopen(event_file, "r");
		if (p_observedUninstallFile == NULL) {
			p_observedUninstallFile = fopen(event_file, "w");
		}

		LOG_ERROR(c_TAG, "fork success");

		int fileDescriptor = inotify_init();
		if (fileDescriptor < 0) {
			LOG_DEBUG(c_TAG, "inotify init failed !!!");
			exit(1);
		}

		int watchDescriptor = inotify_add_watch(
				fileDescriptor,
				env->GetStringUTFChars(path, &b_IS_COPY),
				IN_DELETE);
		//env->GetStringUTFChars(path, &b_IS_COPY),
		if (watchDescriptor < 0) {
			LOG_DEBUG(c_TAG, "inotify_add_watch failed !!!");
			return exit(1);
		}

		void *p_buf = malloc(sizeof(struct inotify_event));
		if (p_buf == NULL) {
			LOG_DEBUG(c_TAG, "malloc failed !!!");
			exit(1);
		}

		LOG_INFO(c_TAG, "start observer !!!");
		size_t readBytesA = read(fileDescriptor, p_buf, sizeof(struct inotify_event));

		//free(p_buf);
		//inotify_rm_watch(fileDescriptor, IN_DELETE);


		while(1) {
			FILE *p_appDir = fopen(event_file, "r");
			// 确认已卸载
			if (p_appDir == NULL) {
				LOG_INFO(c_TAG, "uninstall !!!");

				//read 函数会阻塞线程， run here 说明目录被删除，所以在此处释放监听器内存，注销监听器
				free(p_buf);
				inotify_rm_watch(fileDescriptor, IN_DELETE);

				break;
			} else {

				int fileDescriptor = inotify_init();
				if (fileDescriptor < 0) {
					LOG_DEBUG(c_TAG, "inotify init failed !!!");
					exit(1);
				}

				int watchDescriptorA = inotify_add_watch(
					fileDescriptor,
					env->GetStringUTFChars(path, &b_IS_COPY),
					IN_DELETE);
				if (watchDescriptorA < 0) {
					LOG_DEBUG(c_TAG, "inotify_add_watch failed !!!");

					free(p_buf);
					inotify_rm_watch(fileDescriptor, IN_DELETE);

					exit(1);
				}

				size_t readBytesA = read(fileDescriptor, p_buf, sizeof(struct inotify_event));
			}
		}

		/*
		if(check_watch(env, path) != 0){
			exit(1);
		}
		*/
		/*
		LOG_INFO(c_TAG, "start sleep");
		sleep(4000);
		LOG_INFO(c_TAG, "sleep wake");

		if (access(env->GetStringUTFChars(path, NULL), F_OK) != -1) {
			if (check_watch(env, path) != 0) {
				exit(1);
			}
		}
		*/
		LOG_INFO(c_TAG, "uninstalled !!!");

		if (version < 17) {
			execlp("am", "am",
					"start", "-a",
					"android.intent.action.VIEW",
					"-d", env->GetStringUTFChars(url, NULL), (char *) NULL);
		} else {
			execlp("am", "am",
					"start",
					"--user", "0", "-a",
					"android.intent.action.VIEW",
					"-d", env->GetStringUTFChars(url, NULL), (char *) NULL);
		}
	} else {
		LOG_ERROR(c_TAG, "parent process exit, fork process come in init process");
	}

	LOG_INFO(c_TAG, "end");
}

#ifdef __cplusplus
}
#endif
