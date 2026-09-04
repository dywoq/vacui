# Overview

## Introduction

The IR (stands for Initialization Routine) is a kernel subsystem that sets
the kernel up. The IR depends on the initialization functions of the kernel
subsystems.

## Parameters

Internally, the IR subsystem consists of meta information related to the
procedures. It is not exposed publicly to external kernel subsystems unless
it is stated otherwise. The IR subsystem consists of the following parameters:

- **Initialization Procedure** and **Startup Procedure** (**PUBLIC**)
  Conditions: These separate parameters indicate the procedures' current
  state. They can be changed by the corresponding procedures. They are
  exposed publicly through the IR's APIs. Specific conditions cannot
  be forced despite restrictions. The subsystem is forbidden from
  activating more than one condition.

- **Kernel Subsystems Initialization Order, KSIO** (**INTERNAL**): This parameter is
  a list containing a kernel subsystems' initialization priority. It is needed
  to prevent circular dependency issues, since the kernel subsystems are
  allowed to use others' functionality (dependencies of every kernel subsystem
  are specified in corresponding documents). A kernel subsystem's
  initialization priority is decided using the following rules:

  - As a kernel subsystem's dependencies list increases, its priority
    decreases.
  - Kernel subsystem's dependencies are built first.

### Procedure Conditions

**Initialization Procedure**:

- `Ready`: Indicates that the procedure has not been started yet.
  **Restrictions**: The startup procedure cannot be activated.

- `Failure`: Indicates that the procedure has failed to initialize the
  kernel. **Restrictions**: The condition `Ready` and `Success` cannot be
  activated, and the initialization procedure cannot be started again.

- `Success`: Indicates that the procedure has initialized the kernel
  successfully. **Restrictions**: The condition `Ready` and `Success`
  cannot be activated, and the initialization procedure cannot be
  started again.

**Startup Procedure**:

- `Ready`: Indicates that the procedure has not been started yet.
  **Restrictions**: The startup procedure cannot be activated.

- `Started`: Indicates that the kernel has been started.

## Procedures

The IR subsystem has two procedures: **Initialization** and **Startup**.

- **Initialization Procedure**: This procedure is responsible for
  installing kernel environment and initializing kernel subsystems.
  Any error, which procedure encountered, causes the kernel to halt.
  It is the first procedure started.

- **Startup Procedure**: This procedure is responsible for starting the kernel.
  _Note: Its description expands as more subsystems get their
  own documentation. - dywoq_

### Initialization Procedure Steps

#### Environment Installation

_Description_: This step installs the kernel environment. The kernel
environment implies that everything is configured correctly to make the
kernel properly work.

_Next step_: **Subsystems Initialization**

#### Subsystems Initialization

_Description_: This step uses the KSIO (see the **Parameters** chapter) parameter
to correctly initialize the kernel subsystems. After initializing them,
the step begins the **Startup Procedure**.

### Startup Procedure Steps

_Note: The steps of the procedure will be added as soon as more documents
of the kernel subsystems appear - dywoq_

# API

## Initialization Procedure

Functions, types and macros of the initialization procedure start with
`ir_init` prefix or `IR_INIT` prefix if a symbol is a macro.

### Environment installation

Visibility Scope: Private
Signature:

```c
void
ir_init_environment_installation();
```

This function corresponds to the **"Environment Installation"** step After
environment installation, it calls the **IrInitSubsystemsInitialization**
function.

It is implemented fully in Assembly to prevent accidental stack usage.
Before the procedure configures stack, the stack still contains a
physical address of the boot loader stack.

### Subsystems initialization

Visibility Scope: Private
Signature:

```c
void ir_init_subsystems_initialization();
```

This function corresponds to the **"Subsystems Initialization"** step.

### Inspecting the public information

Visibility Scope: Public
Signature:

```c
bool ir_init_inspect_info(ir_init_info_t *dest_info);
```

Parameters:

- `dest_info` **OUT** - A required pointer to the destination `ir_init_info_t`
  structure instance.

  `ir_init_info` structure:

  ```c
  typedef struct ir_init_info {
      ir_init_condition_t condition;
  } ir_init_info_t;
  ```
  - `condition` - This field corresponds to the public condition
    parameter of the initialization routine.

  `ir_init_condition-t` enumeration:

  ```c
  typedef enum ir_init_condition : vq_ubyte {
      ir_init_condition_ready = 0,
      ir_init_condition_success,
      ir_init_condition_failure
  } ir_init_condition_t;
  ```

Returns:

- `true` - The information have been written successfully.
- `false` - The `dest_info` parameter is null.

This function writes information to the provided destination instance.

## Startup Procedure

_Note: As mentioned earlier, the startup procedure description is not ready
yet. - dywoq_
