else {

      //foreground
      if (bg == 0) {
//          wait(NULL);
//          sio_puts("ok");
          //blocl signals
//          printf("hereee");

          sigset_t sigs;
          sigemptyset(&sigs);
          sigaddset(&sigs, SIGINT);
          sigaddset(&sigs, SIGTSTP);
          sigaddset(&sigs, SIGCHLD);

          sigprocmask(SIG_BLOCK, &sigs, NULL);
          if (builtin_cmd(argv1) == 0) {
              int pid = fork();
              if (pid == 0) {
                  sigprocmask(SIG_UNBLOCK, &sigs, NULL);
                  execve(argv1[0], argv1, environ);
              } else {
//                sigprocmask(SIG_UNBLOCK, &sigs, NULL);
                addjob(jobs, pid, FG, cmdline);
                int status;
                waitpid(pid, &status, 0);
                sigprocmask(SIG_UNBLOCK, &sigs, NULL);
              }
          }
      //background
      } else {
          sigset_t sigs;
          sigemptyset(&sigs);
          sigaddset(&sigs, SIGINT);
          sigaddset(&sigs, SIGCHLD);
          sigaddset(&sigs, SIGTSTP);

          sigprocmask(SIG_BLOCK, &sigs, NULL);

          if (builtin_cmd(argv1) == 0) {
            int pid = fork();
            if (pid == 0) {
                  sigprocmask(SIG_UNBLOCK, &sigs, NULL);
                  execve(argv1[0], argv1, environ);
            } else {
              addjob(jobs, pid, BG, cmdline);
              printjob(getjobjid(jobs, nextjid-1));
//              sigprocmask(SIG_UNBLOCK, &sigs, NULL);

            }
         }
//          wait(NULL);
      }
