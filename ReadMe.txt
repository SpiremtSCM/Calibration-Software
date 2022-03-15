YC Note:

Last update Nov 23, 2016

Re-design dialog SetZeroDlg, adding new input for valve voltage control. Operators now are able to control voltage for each stage of calibration

Operators must fill all blanks in SetZeroDlg 



YC Note:

Last update Nov 22, 2016

Re-design dialog SetZeroDlg, adding input for pump waiting and sampling time;

Modified SetZeroDlg.cpp to reflect the dialog change, new parameter m_wait_time and m_sample_time are added to store the respective value

Sleep() function is removed from SetZeroDlg.cpp, this function cause bug in release mode



YC Note:

Last updated Oct 9, 2016

The delay time for auto calibration is changed to 5min


YC Note:

Last updated May 31, 2016

The reference meter's address is updated to new address
The database now should be STOCK-ROOM/SPIRESERVER, the user should be "lab"
A bug is fixed in ColletDlg.cpp

This is the alpha testing version of the calibration software, which can support
EF10 and EF11.

Simply copy and paste the release or debug folder to your local computer to run.
However, NI daq driver and SQL server express must be installed on the local machine.

There is no major difference between debug and release folder. The debug version 
may be slower.

========================================================================
       MICROSOFT FOUNDATION CLASS LIBRARY : Calibration
========================================================================


AppWizard has created this Calibration application for you.  This application
not only demonstrates the basics of using the Microsoft Foundation classes
but is also a starting point for writing your application.

This file contains a summary of what you will find in each of the files that
make up your Calibration application.

Calibration.dsp
    This file (the project file) contains information at the project level and
    is used to build a single project or subproject. Other users can share the
    project (.dsp) file, but they should export the makefiles locally.

Calibration.h
    This is the main header file for the application.  It includes other
    project specific headers (including Resource.h) and declares the
    CCalibrationApp application class.

Calibration.cpp
    This is the main application source file that contains the application
    class CCalibrationApp.

Calibration.rc
    This is a listing of all of the Microsoft Windows resources that the
    program uses.  It includes the icons, bitmaps, and cursors that are stored
    in the RES subdirectory.  This file can be directly edited in Microsoft
	Visual C++.

Calibration.clw
    This file contains information used by ClassWizard to edit existing
    classes or add new classes.  ClassWizard also uses this file to store
    information needed to create and edit message maps and dialog data
    maps and to create prototype member functions.

res\Calibration.ico
    This is an icon file, which is used as the application's icon.  This
    icon is included by the main resource file Calibration.rc.

res\Calibration.rc2
    This file contains resources that are not edited by Microsoft 
	Visual C++.  You should place all resources not editable by
	the resource editor in this file.




/////////////////////////////////////////////////////////////////////////////

AppWizard creates one dialog class:

CalibrationDlg.h, CalibrationDlg.cpp - the dialog
    These files contain your CCalibrationDlg class.  This class defines
    the behavior of your application's main dialog.  The dialog's
    template is in Calibration.rc, which can be edited in Microsoft
	Visual C++.


/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named Calibration.pch and a precompiled types file named StdAfx.obj.

Resource.h
    This is the standard header file, which defines new resource IDs.
    Microsoft Visual C++ reads and updates this file.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" to indicate parts of the source code you
should add to or customize.

If your application uses MFC in a shared DLL, and your application is 
in a language other than the operating system's current language, you
will need to copy the corresponding localized resources MFC42XXX.DLL
from the Microsoft Visual C++ CD-ROM onto the system or system32 directory,
and rename it to be MFCLOC.DLL.  ("XXX" stands for the language abbreviation.
For example, MFC42DEU.DLL contains resources translated to German.)  If you
don't do this, some of the UI elements of your application will remain in the
language of the operating system.

/////////////////////////////////////////////////////////////////////////////
