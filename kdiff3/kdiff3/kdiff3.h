/***************************************************************************
                          kdiff3.h  -  description
                             -------------------
    begin                : Don Jul 11 12:31:29 CEST 2002
    copyright            : (C) 2002 by Joachim Eibl
    email                : joachim.eibl@gmx.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

/***************************************************************************
 * $Log$
 * Revision 1.1  2002/08/18 16:24:16  joachim99
 * Initial revision
 *                                                                   *
 ***************************************************************************/

#ifndef KDIFF3_H
#define KDIFF3_H
 

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

// include files for Qt
#include <qdialog.h>

// include files for KDE 
#include <kapp.h>
#include <kmainwindow.h>
#include <kaccel.h>
#include <kaction.h>
#include <kurl.h>

#include "diff.h"

// forward declaration of the KDiff3 classes
class OptionDialog;

class QScrollBar;
class QComboBox;

/**
  * The base class for KDiff3 application windows. It sets up the main
  * window and reads the config file as well as providing a menubar, toolbar
  * and statusbar. An instance of KDiff3View creates your center view, which is connected
  * to the window's Doc object.
  * KDiff3App reimplements the methods that KMainWindow provides for main window handling and supports
  * full session management as well as using KActions.
  * @see KMainWindow
  * @see KApplication
  * @see KConfig
  *
  * @author Source Framework Automatically Generated by KDevelop, (c) The KDevelop Team.
  * @version KDevelop version 1.2 code generation
  */
class KDiff3App : public KMainWindow
{
  Q_OBJECT


  public:
    /** construtor of KDiff3App, calls all init functions to create the application.
     */
    KDiff3App(QWidget* parent=0, const char* name=0);
    ~KDiff3App();


  protected:
    /** save general Options like all bar positions and status as well as the geometry and the recent file list to the configuration
     * file
     */ 	
    void saveOptions();
    /** read general Options again and initialize all variables like the recent file list
     */
    void readOptions();
    /** initializes the KActions of the application */
    void initActions();
    /** sets up the statusbar for the main window by initialzing a statuslabel.
     */
    void initStatusBar();

    /** creates the centerwidget of the KMainWindow instance and sets it as the view
     */
    void initView();
    /** queryClose is called by KMainWindow on each closeEvent of a window. Against the
     * default implementation (only returns true), this calles saveModified() on the document object to ask if the document shall
     * be saved if Modified; on cancel the closeEvent is rejected.
     * @see KMainWindow#queryClose
     * @see KMainWindow#closeEvent
     */
    virtual bool queryClose();
    /** queryExit is called by KMainWindow when the last window of the application is going to be closed during the closeEvent().
     * Against the default implementation that just returns true, this calls saveOptions() to save the settings of the last window's	
     * properties.
     * @see KMainWindow#queryExit
     * @see KMainWindow#closeEvent
     */
    virtual bool queryExit();


  public slots:

    /** open a file and load it into the document*/
    void slotFileOpen();
    /** save a document */
    void slotFileSave();
    /** save a document by a new filename*/
    void slotFileSaveAs();
    /** asks for saving if the file is modified, then closes the actual file and window*/
    void slotFileClose();

    /** closes all open windows by calling close() on each memberList item until the list is empty, then quits the application.
     * If queryClose() returns false because the user canceled the saveModified() dialog, the closing breaks.
     */
    void slotFileQuit();
    /** put the marked text/object into the clipboard and remove
     *	it from the document
     */
    void slotEditCut();
    /** put the marked text/object into the clipboard
     */
    void slotEditCopy();
    /** paste the clipboard into the document
     */
    void slotEditPaste();
    /** toggles the toolbar
     */
    void slotViewToolBar();
    /** toggles the statusbar
     */
    void slotViewStatusBar();
    /** changes the statusbar contents for the standard label permanently, used to indicate current actions.
     * @param text the text that is displayed in the statusbar
     */
    void slotStatusMsg(const QString &text);

  private:
    /** the configuration object of the application */
    KConfig *config;

    // KAction pointers to enable/disable actions
    KAction* fileOpen;
    KAction* fileSave;
    KAction* fileSaveAs;
    KAction* fileQuit;
    KAction* editCut;
    KAction* editCopy;
    KAction* editPaste;
    KToggleAction* viewToolBar;
    KToggleAction* viewStatusBar;

////////////////////////////////////////////////////////////////////////
// Special KDiff3 specific stuff starts here

    KAction *goTop;
    KAction *goBottom;
    KAction *goPrevConflict;
    KAction *goNextConflict;
    KAction *goPrevDelta;
    KAction *goNextDelta;
    KToggleAction *chooseA;
    KToggleAction *chooseB;
    KToggleAction *chooseC;

    QScrollBar* m_pHScrollBar;
    QScrollBar* m_pDiffVScrollBar;
    QScrollBar* m_pMergeVScrollBar;

    DiffTextWindow* m_pDiffTextWindow1;
    DiffTextWindow* m_pDiffTextWindow2;
    DiffTextWindow* m_pDiffTextWindow3;

    MergeResultWindow* m_pMergeResultWindow;

    Overview* m_pOverview;

    QWidget* m_pCornerWidget;


   QString m_filename1;
   const char* m_pBuf1;
   int m_size1;
   int m_v1size; // Nr of lines in m_pBuf1 and size of m_v1, m_dv12 and m_dv13
   std::vector<LineData> m_v1;

   QString m_filename2;
   const char* m_pBuf2;
   int m_size2;
   int m_v2size;
   std::vector<LineData> m_v2;

   QString m_filename3;
   const char* m_pBuf3;
   int m_size3;
   int m_v3size;
   std::vector<LineData> m_v3;

   QString m_outputFilename;
   bool m_bDefaultFilename;

   DiffList m_diffList12;
   DiffList m_diffList23;
   DiffList m_diffList13;

   Diff3LineList m_diff3LineList;

   int m_neededLines;
   int m_maxWidth;
   int m_DTWHeight;
   bool m_bOutputModified;

   OptionDialog* m_pOptionDialog;

   void init( const char* filename1, const char* filename2, const char* filename3 );

   virtual bool eventFilter( QObject* o, QEvent* e );
   virtual void resizeEvent(QResizeEvent*);
//   virtual void timerEvent(QTimerEvent*);
private slots:
   void resizeDiffTextWindow(int newWidth, int newHeight);
   void resizeMergeResultWindow();
   void scrollDiffTextWindow( int deltaX, int deltaY );
   void scrollMergeResultWindow( int deltaX, int deltaY );
   void setDiff3Line( int line );
   void sourceMask( int srcMask, int enabledMask );

   void slotGoTop();
   void slotGoBottom();
   void slotGoPrevConflict();
   void slotGoNextConflict();
   void slotGoPrevDelta();
   void slotGoNextDelta();
   void slotChooseA();
   void slotChooseB();
   void slotChooseC();
   void slotConfigure();
   void slotRefresh();
   void slotSelectionEnd();
   void slotSelectionStart();
   void slotClipboardChanged();
   void slotOutputModified();
   void slotOutputSavable(bool);
};

class QCheckBox;

class OpenDialog : public QDialog
{
   Q_OBJECT
public:
   OpenDialog(
      QWidget* pParent, const char* n1, const char* n2, const char* n3,
      bool bMerge, const char* outputName, const char* slotConfigure, OptionDialog* pOptions  );

   QComboBox* m_lineA;
   QComboBox* m_lineB;
   QComboBox* m_lineC;
   QComboBox* m_lineOutput;
   QCheckBox* m_pMerge;
   virtual void accept();
private:
   OptionDialog* m_pOptions;

private slots:
   void selectFileA();
   void selectFileB();
   void selectFileC();
   void selectOutputName();
   void internalSlot(int);
signals:
   void internalSignal(bool);
};
#endif // KDIFF3_H
