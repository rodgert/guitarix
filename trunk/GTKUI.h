#ifndef GTKUI_H
#define GTKUI_H


class GTKUI : public UI
{
private :
    static bool			fInitialized;
    static list<UI*>	fGuiList;

protected :
    //GtkWidget* 	fWindow;
    int			fTop;
    GtkWidget* 	fBox[stackSize];
    int 		fMode[stackSize];
    bool		fStopped;

    GtkWidget* addWidget(const char* label, GtkWidget* w);
    virtual void pushBox(int mode, GtkWidget* w);

public :

    static const gboolean expand = TRUE;
    static const gboolean fill = TRUE;
    static const gboolean homogene = FALSE;

    GTKUI(char * name, int* pargc, char*** pargv);

    // -- layout groups
    virtual void openFrameBox(const char* label);
    virtual void openHorizontalBox(const char* label = "");
    virtual void openVerticalBox(const char* label = "");
    virtual void openDialogBox(const char* label, float* zone);
    virtual void openEventBox(const char* label = "");
    virtual void openHandleBox(const char* label = "");
    virtual void openExpanderBox(const char* label, float* zone);
    virtual void closeBox();

    // -- active widgets
    virtual void addMenu();
    virtual void addButton(const char* label, float* zone);
    virtual void addToggleButton(const char* label, float* zone);
    virtual void addPToggleButton(const char* label, float* zone);
    virtual void addJToggleButton(const char* label, float* zone);
    virtual void addCheckButton(const char* label, float* zone);
    virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step);
    virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step);

    virtual void show();
    virtual void run();
    virtual void run_nogui();

};

#endif // GTKUI_H
