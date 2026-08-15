FOREACH (SOURCE ${SOURCES})
        IF (SOURCE MATCHES "\\.C$")
                SET_SOURCE_FILES_PROPERTIES (
                        ${SOURCE}
                        PROPERTIES
                        LANGUAGE C)
        ENDIF ()
ENDFOREACH ()

FOREACH (SOURCE ${SOURCES})
        IF (SOURCE MATCHES "\\.CPP$")
                SET_SOURCE_FILES_PROPERTIES (
                        ${SOURCE}
                        PROPERTIES
                        LANGUAGE CXX)
        ENDIF ()
ENDFOREACH ()

FOREACH (SOURCE ${SOURCES})
        IF (SOURCE MATCHES "\\.ASM$")
                SET_SOURCE_FILES_PROPERTIES (
                        ${SOURCE}
                        PROPERTIES
                        LANGUAGE ASM_NASM)
        ENDIF ()
ENDFOREACH ()
