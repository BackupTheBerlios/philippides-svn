SUBDIRS = xslt pics
# set the include path for X, qt and KDE
INCLUDES = $(all_includes) -I/usr/include/libxml2 

# these are the headers for your project
noinst_HEADERS = philippides.h \
		 Athlet.h \
		 AthletDtd.h \
		 Run.h \
		 RunDtd.h \
		 Exceptions.h \
		 DbWidget.h \
		 Wizard.h \
		 AthletParser.h \
		 RunParser.h \
		 RunDialog.h \
		 RunListViewItem.h \
		 StatsDialog.h \
		 StatsWidget.h \
		 RunPtrList.h \
		 TrackEditorDialog.h \
		 MapWidget.h

# let automoc handle all of the meta source files (moc)
METASOURCES = AUTO

messages: rc.cpp
	$(XGETTEXT) *.cpp -o $(podir)/philippides.pot

KDE_ICON = philippides

#########################################################################
# APPLICATION SECTION
#########################################################################
# this is the program that gets installed.  it's name is used for all
# of the other Makefile.am variables
bin_PROGRAMS = philippides

# the application source, library search path, and link libraries
philippides_SOURCES = 	main.cpp \
			philippides.cpp \
			Athlet.cpp \
			Run.cpp \
			DbWidgetBase.ui \
			DbWidget.cpp \
			WizardBase.ui \
			Wizard.cpp \
			AthletParser.cpp \
			RunParser.cpp \
			RunDialogBase.ui \
			RunDialog.cpp \
			RunListViewItem.cpp \
			StatsDialogBase.ui \
			StatsDialog.cpp \
			StatsWidget.cpp \
			RunPtrList.cpp \
			TrackEditorDialogBase.ui \
			TrackEditorDialog.cpp \
			MapWidget.cpp
			
 
philippides_LDFLAGS = $(KDE_RPATH) $(all_libraries)  
 
philippides_LDADD = $(LIB_KDEUI) $(LIB_KHTML) -lxslt -lxml2 -lz -lpthread -lm
# this is where the desktop file will go 
kdelnkdir   = $(kde_appsdir)/Utilities
kdelnk_DATA = philippides.desktop

# this is where the shell's XML-GUI resource file goes
rcdir   = $(kde_datadir)/philippides
rc_DATA = philippidesui.rc

