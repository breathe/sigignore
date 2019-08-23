# Description

Native extension for node to set sigterm handler to SIG_IGN.

When a handler is set to SIG_IGN, the behavior of that handler is inherited within sub-processes
created by execve:

From - http://man7.org/linux/man-pages/man7/signal.7.html

> A child created via fork(2) inherits a copy of its parent's signal
> dispositions. During an execve(2), the dispositions of handled
> signals are reset to the default; the dispositions of ignored signals
> are left unchanged.

Its not possible to set a signal handler to SIG_IGN from node using javascript. Hence this module.

## How to use

```javascript
import { ignoreSigterm } from "sigignore";

// set SIGTERM to SIG_IGN
ignoreSigterm();
```

## Why

Mainly to get correct behavior on heroku.

When dyno's are shutdown (say in response to a downscale event) -- heroku first sends SIGTERM to all processes running on dyno to let them know they should shutdown (then 30 seconds later sends SIGKILL to force them all to end). This is to allow a process team to cleanly shutdown before the dyno is destroyed.

In my scenario, I launch node processes inside a ruby DelayedJob worker. Delayed job worker's SIGTERM handler arranges to keep running until the current job is finished. My node process in turn, might create subprocesses during the course of its execution -- I want those to inherit SIG_TERM => SIG_IGN behavior so that hopefully the node tasks invoked during the DJ job execution will run to completion and then everything shut down and the code will reach consistent shutdown state when the delayed job task completes.
