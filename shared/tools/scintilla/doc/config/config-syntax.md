# Configuration syntax

- Scintilla uses the keys to store the information inside the configurations, 
and supports multi-line values:
```conf
KEY = FOO
KEY_MULTILINE = FOO \
                XYZ \
                FOO1 \
                FOO2
```

- Scintilla supports hash comments. WARNING: Hash comments must be placed on its own line,
otherwise, your comment is included into the value:

**CORRECT**:
```conf
# Comment!
KEY = FOO
```

**WRONG**:
```conf
# The comment is included in the key's value
KEY = FOO # Comment! 
```

- Scintilla uses config and environment variables expansion to get their values.
If variable is not found within configuration, Scintilla retrieves environment variable.
If both operations don't succeed, Scintilla aborts the parsing and prints an error.

**CONFIG VARIABLE**:
```conf
FOO = XYZ
KEY = ${FOO}
```

**ENVIRONMENT VARIABLE (variable with that name wasn't found within configuration)**
```conf
KEY = ${PWD}
```

