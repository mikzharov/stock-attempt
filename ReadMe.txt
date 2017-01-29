========================================================================
    CONSOLE APPLICATION : Stock Attempt Project Overview
========================================================================

Please ignore the OpenCL branch, it failed to run faster than the master branch, and also crashed the graphics driver often.

The master branch contains the main program used to try and apply GP to the stock market. This project didn't actually manage to "find the secrets" of the stock market (if it did, I wouldn't be in school). However it served as a great launch point for learning C++;

Some assumptions made while writing this program are:
* It is possible to make smart decision on whether to buy or sell a stock based solely on its market performance (specifically using only high, low, close, open, adjusted and volume information from the past).
* The programs activity will not affect the stock market, just so that its effect does not have to be accounted for.

Pit falls: 
* Local maxima are a really big problem. An individual with a decent fitness dominates everything else because it is easy to create that individual, and hard to weed it out.
* Processing power is a problem, this runs pretty slow.
* The programs have never made more money than has originally been given to them.


Stock Attempt.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

Stock Attempt.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

Stock Attempt.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named Stock Attempt.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////