#import <AVFoundation/AVFoundation.h>
#import <dispatch/dispatch.h>
#include <stdio.h>

bool requestMicrophonePermission() {
  if (@available(macOS 10.14, *)) {
    AVAuthorizationStatus status = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeAudio];

    if (status == AVAuthorizationStatusAuthorized) {
      fprintf(stderr, "MicPermission: already authorized\n");
      return true;
    }

    if (status == AVAuthorizationStatusDenied || status == AVAuthorizationStatusRestricted) {
      fprintf(stderr, "MicPermission: denied or restricted (status=%d)\n", (int)status);
      return false;
    }

    // Not determined - request permission
    fprintf(stderr, "MicPermission: requesting permission...\n");
    __block bool granted = false;
    dispatch_semaphore_t sem = dispatch_semaphore_create(0);
    [AVCaptureDevice requestAccessForMediaType:AVMediaTypeAudio completionHandler:^(BOOL g) {
      granted = g;
      dispatch_semaphore_signal(sem);
    }];
    dispatch_semaphore_wait(sem, dispatch_time(DISPATCH_TIME_NOW, 30LL * NSEC_PER_SEC));
    fprintf(stderr, "MicPermission: user responded, granted=%d\n", (int)granted);
    return granted;
  }

  // Pre-10.14, no permission needed
  return true;
}
