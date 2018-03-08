#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/source/InstallPG.o \
	${OBJECTDIR}/source/StartPG.o \
	${OBJECTDIR}/source/db/db_Categories.o \
	${OBJECTDIR}/source/db/db_CategoriesRelation.o \
	${OBJECTDIR}/source/db/db_Comments.o \
	${OBJECTDIR}/source/db/db_Log.o \
	${OBJECTDIR}/source/db/db_PostStatus.o \
	${OBJECTDIR}/source/db/db_Posts.o \
	${OBJECTDIR}/source/db/db_Session.o \
	${OBJECTDIR}/source/db/db_Setting.o \
	${OBJECTDIR}/source/db/db_Tags.o \
	${OBJECTDIR}/source/db/db_TagsRelation.o \
	${OBJECTDIR}/source/db/db_UserAccess.o \
	${OBJECTDIR}/source/db/db_Users.o \
	${OBJECTDIR}/source/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m64
CXXFLAGS=-m64

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lpthread -lpq ../../mxchat/XWeb/dist/debug_static_lib/GNU-Linux/libxweb.a ../../mxsql/PG/MxSql/dist/DLinux/GNU-Linux/libmxsql.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mxblog

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mxblog: ../../mxchat/XWeb/dist/debug_static_lib/GNU-Linux/libxweb.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mxblog: ../../mxsql/PG/MxSql/dist/DLinux/GNU-Linux/libmxsql.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mxblog: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mxblog ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/source/InstallPG.o: source/InstallPG.cpp
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/postgresql -I../../mxchat/XWeb/source -I../../mxsql/PG/MxSql/source -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/InstallPG.o source/InstallPG.cpp

${OBJECTDIR}/source/StartPG.o: source/StartPG.cpp
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/postgresql -I../../mxchat/XWeb/source -I../../mxsql/PG/MxSql/source -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/StartPG.o source/StartPG.cpp

${OBJECTDIR}/source/db/db_Categories.o: source/db/db_Categories.cpp
	${MKDIR} -p ${OBJECTDIR}/source/db
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/postgresql -I../../mxchat/XWeb/source -I../../mxsql/PG/MxSql/source -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/db/db_Categories.o source/db/db_Categories.cpp

${OBJECTDIR}/source/db/db_CategoriesRelation.o: source/db/db_CategoriesRelation.cpp
	${MKDIR} -p ${OBJECTDIR}/source/db
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/postgresql -I../../mxchat/XWeb/source -I../../mxsql/PG/MxSql/source -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/db/db_CategoriesRelation.o source/db/db_CategoriesRelation.cpp

${OBJECTDIR}/source/db/db_Comments.o: source/db/db_Comments.cpp
	${MKDIR} -p ${OBJECTDIR}/source/db
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/postgresql -I../../mxchat/XWeb/source -I../../mxsql/PG/MxSql/source -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/db/db_Comments.o source/db/db_Comments.cpp

${OBJECTDIR}/source/db/db_Log.o: source/db/db_Log.cpp
	${MKDIR} -p ${OBJECTDIR}/source/db
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/postgresql -I../../mxchat/XWeb/source -I../../mxsql/PG/MxSql/source -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/db/db_Log.o source/db/db_Log.cpp

${OBJECTDIR}/source/db/db_PostStatus.o: source/db/db_PostStatus.cpp
	${MKDIR} -p ${OBJECTDIR}/source/db
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/postgresql -I../../mxchat/XWeb/source -I../../mxsql/PG/MxSql/source -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/db/db_PostStatus.o source/db/db_PostStatus.cpp

${OBJECTDIR}/source/db/db_Posts.o: source/db/db_Posts.cpp
	${MKDIR} -p ${OBJECTDIR}/source/db
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/postgresql -I../../mxchat/XWeb/source -I../../mxsql/PG/MxSql/source -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/db/db_Posts.o source/db/db_Posts.cpp

${OBJECTDIR}/source/db/db_Session.o: source/db/db_Session.cpp
	${MKDIR} -p ${OBJECTDIR}/source/db
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/postgresql -I../../mxchat/XWeb/source -I../../mxsql/PG/MxSql/source -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/db/db_Session.o source/db/db_Session.cpp

${OBJECTDIR}/source/db/db_Setting.o: source/db/db_Setting.cpp
	${MKDIR} -p ${OBJECTDIR}/source/db
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/postgresql -I../../mxchat/XWeb/source -I../../mxsql/PG/MxSql/source -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/db/db_Setting.o source/db/db_Setting.cpp

${OBJECTDIR}/source/db/db_Tags.o: source/db/db_Tags.cpp
	${MKDIR} -p ${OBJECTDIR}/source/db
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/postgresql -I../../mxchat/XWeb/source -I../../mxsql/PG/MxSql/source -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/db/db_Tags.o source/db/db_Tags.cpp

${OBJECTDIR}/source/db/db_TagsRelation.o: source/db/db_TagsRelation.cpp
	${MKDIR} -p ${OBJECTDIR}/source/db
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/postgresql -I../../mxchat/XWeb/source -I../../mxsql/PG/MxSql/source -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/db/db_TagsRelation.o source/db/db_TagsRelation.cpp

${OBJECTDIR}/source/db/db_UserAccess.o: source/db/db_UserAccess.cpp
	${MKDIR} -p ${OBJECTDIR}/source/db
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/postgresql -I../../mxchat/XWeb/source -I../../mxsql/PG/MxSql/source -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/db/db_UserAccess.o source/db/db_UserAccess.cpp

${OBJECTDIR}/source/db/db_Users.o: source/db/db_Users.cpp
	${MKDIR} -p ${OBJECTDIR}/source/db
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/postgresql -I../../mxchat/XWeb/source -I../../mxsql/PG/MxSql/source -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/db/db_Users.o source/db/db_Users.cpp

${OBJECTDIR}/source/main.o: source/main.cpp
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/postgresql -I../../mxchat/XWeb/source -I../../mxsql/PG/MxSql/source -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/source/main.o source/main.cpp

# Subprojects
.build-subprojects:
	cd ../../mxchat/XWeb && ${MAKE}  -f Makefile CONF=debug_static_lib
	cd ../../mxsql/PG/MxSql && ${MAKE}  -f Makefile CONF=DLinux

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:
	cd ../../mxchat/XWeb && ${MAKE}  -f Makefile CONF=debug_static_lib clean
	cd ../../mxsql/PG/MxSql && ${MAKE}  -f Makefile CONF=DLinux clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
