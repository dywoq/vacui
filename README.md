Vacui is an x86 operating system developed entirely inside emulated Windows NT 4 Workstation, replicating the authentic NT-era development workflow.

Built using `C++`,  and `MSVC 6.0`.
# Workflow
Environment is 86box emulator. I test my operating system in 86box with fixed hardware config.

My main workflow:
- To track changes, **they're written in change logs**. Each tool/subsystem has its own change log: For example, if I fixed a bug in `tools/vmake`, I must write it in `tools/vmake/changelog/<year>/<month>/<day>.txt`. It happens inside Windows NT 4 Workstation itself. **Note**: Changes are pushed only if my working day is done, or the feature/fix works well.
- A disk with project is mounted to the Linux kernel and its content is copied to the local git repository clone.
- All the files are copied into the local git repository. The Git detects the changed files for staging, where only new/changed files can be commited.
- Commit is made in this format:
```
Push <day>-<month> <year> changes

Changelog:
- <subsystem/tool>: <subsystem/tool>/changelog/<year/<month>/<day>.txt>
<other changed subsystems are texted here>

Signed-off-by: foo@gmail.com
```
- After the commit is done, I push it to the main branch.
# License
The project is published under MIT License.
