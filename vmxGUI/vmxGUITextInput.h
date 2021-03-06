/*=========================================================================
 
 Program:   mipx
 Module:    vmxGUITextInput.h
 
 Authors: Danilo Babin.
 Copyright (c) Danilo Babin.
 All rights reserved.
 See Copyright.txt
 
 Licensed under the BSD License 2.0.
 
 This software is distributed WITHOUT ANY WARRANTY; without even
 the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 PURPOSE. See the above copyright notice for more information.
 
 =========================================================================*/



#if defined(vmxGUITextInput_USE_SOURCE_CODE) || defined(vmxCore_USE_SOURCE_CODE)
    #define vmxGUITextInput_API
#else
    #if defined(_MSC_VER)
        #ifdef vmxGUITextInput_EXPORTS
            #define vmxGUITextInput_API __declspec(dllexport)
        #else
            #define vmxGUITextInput_API __declspec(dllimport)
        #endif
    #else
        #ifdef vmxGUITextInput_EXPORTS
            #define vmxGUITextInput_API __attribute__((visibility("default")))
        #else
            #define vmxGUITextInput_API
        #endif
    #endif
#endif



#ifndef vmxGUITextInput_H
#define vmxGUITextInput_H



#include <stdint.h>
#include "mxArray.h"
#include "mxString.h"
#include "vmxGUIClipBoard.h"
#include "vmxGUIObject.h"


#include <vtkCallbackCommand.h>
#include <vtkCommand.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRendererCollection.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>







// Pre-declaration.
class vmxGUITextInput;



//class vmxGUITextInput_API vmxGUITextInputInteractorLeftButtonDownCallback : public vtkCommand
//{
//    
//public:
//    
//    /// Pointer to text input that uses this callback.
//    vmxGUITextInput *m_text_input;
//    
//    /// Constructor.
//    vmxGUITextInputInteractorLeftButtonDownCallback();
//    
//    /// Destructor.
//    ~vmxGUITextInputInteractorLeftButtonDownCallback();
//    
//    /// Initialize the text input linked to this callback
//    void SetTextInput(vmxGUITextInput *text_input);
//    
//    /// Create new object instance.
//    static vmxGUITextInputInteractorLeftButtonDownCallback* New();
//    
//    /// Method that executes when the callback is called.
//    virtual void Execute(vtkObject *caller, unsigned long, void *);
//};



class vmxGUITextInput_API vmxIntInputInteractorKeyPressCallback : public vtkCommand
{
    
public:
    
    /// Pointer to text input that uses this callback.
    vmxGUITextInput *m_text_input;
    
    /// Constructor.
    vmxIntInputInteractorKeyPressCallback();
    
    /// Destructor.
    ~vmxIntInputInteractorKeyPressCallback();
    
    /// Initialize the text input linked to this callback
    void SetTextInput(vmxGUITextInput *text_input);
    
    /// Create new object instance.
    static vmxIntInputInteractorKeyPressCallback* New();
    
    /// Method that executes when the callback is called.
    virtual void Execute(vtkObject *caller, unsigned long, void *);
};


class vmxGUITextInput_API vmxDoubleInputInteractorKeyPressCallback : public vtkCommand
{
    
public:
    
    /// Pointer to text input that uses this callback.
    vmxGUITextInput *m_text_input;
    
    /// Constructor.
    vmxDoubleInputInteractorKeyPressCallback();
    
    /// Destructor.
    ~vmxDoubleInputInteractorKeyPressCallback();
    
    /// Initialize the text input linked to this callback
    void SetTextInput(vmxGUITextInput *text_input);
    
    /// Create new object instance.
    static vmxDoubleInputInteractorKeyPressCallback* New();
    
    /// Method that executes when the callback is called.
    virtual void Execute(vtkObject *caller, unsigned long, void *);
};


class vmxGUITextInput_API vmxGUITextInputInteractorKeyPressCallback : public vtkCommand
{
    
public:
    
    /// Pointer to text input that uses this callback.
    vmxGUITextInput *m_text_input;
    
    /// Constructor.
    vmxGUITextInputInteractorKeyPressCallback();
    
    /// Destructor.
    ~vmxGUITextInputInteractorKeyPressCallback();
    
    /// Initialize the text input linked to this callback
    void SetTextInput(vmxGUITextInput *text_input);
    
    /// Create new object instance.
    static vmxGUITextInputInteractorKeyPressCallback* New();
    
    /// Method that executes when the callback is called.
    virtual void Execute(vtkObject *caller, unsigned long, void *);
};



class vmxGUITextInput_API vmxGUITextInputInteractorLeftButtonUpCallback : public vtkCommand
{
    
public:
    
    /// Pointer to text input that uses this callback.
    vmxGUITextInput *m_text_input;
    
    /// Constructor.
    vmxGUITextInputInteractorLeftButtonUpCallback();
    
    /// Destructor.
    ~vmxGUITextInputInteractorLeftButtonUpCallback();
    
    /// Initialize the text input linked to this callback
    void SetTextInput(vmxGUITextInput *text_input);
    
    /// Create new object instance.
    static vmxGUITextInputInteractorLeftButtonUpCallback* New();
    
    /// Method that executes when the callback is called.
    virtual void Execute(vtkObject *caller, unsigned long, void *);
};








class vmxGUITextInput_API vmxGUITextInput : public vmxGUIObject
{
    
public:
    
    /// Types of inputs.
    enum vmxInputType
    {
        INTEGER,
        DOUBLE,
        ITEM,
        TEXT //default it text.
    };
    
    /// Input type of this object.
    vmxInputType m_input_type;
    
    /// Pointer to clipboard this object uses.
    vmxGUIClipBoard *m_clip_board;
    
    /// Description text that precedes the input.
    mxString m_description;
    
    /// Input string.
    mxString m_input;
    
    /// Assigned VTK Render Window Interactor.
    vtkRenderWindowInteractor *m_interactor;
    
    /// Indicates if the text input was picked for key text input (i.e. if it is observing the key press events).
    int m_is_keypress_active;
    
    /// Font size of the used chacaters.
    int m_font_size;
    
    /// Actor containing the text.
    vtkSmartPointer<vtkTextActor> m_text_actor;
    
//    /// Callback executed when the left button is pressed.
//    vtkSmartPointer<vmxGUITextInputInteractorLeftButtonDownCallback> m_left_button_down_callback;
    
    /// Callback executed when the left button is released.
    vtkSmartPointer<vmxGUITextInputInteractorLeftButtonUpCallback> m_left_button_up_callback;
    
    /// Callback executed when the key is pressed.
    vtkSmartPointer<vmxGUITextInputInteractorKeyPressCallback> m_key_press_callback_input_text;

    /// Callback executed when the key is pressed.
    vtkSmartPointer<vmxDoubleInputInteractorKeyPressCallback> m_key_press_callback_input_double;

    /// Callback executed when the key is pressed.
    vtkSmartPointer<vmxIntInputInteractorKeyPressCallback> m_key_press_callback_input_integer;

    
    
    /// Constructor.
    vmxGUITextInput();
    
    /// Destructor.
    ~vmxGUITextInput();
    
    /// Create new object instance.
    static vmxGUITextInput* New();
    
    /// Get origin (position) of the whole object.
    void GetOrigin(int &origin1, int &origin2);
    
    /// Get the size of the whole object (all actors together).
    void GetSize(int &output_size1, int &output_size2);
    
    /// Get the size of the menu text actor.
    int GetSizeOfTextActor(int &output_size1, int &output_size2);
    
    /// Check if the user entered a dot '.' into the input string. To be used for input of real numbers.
    int IsDotEntered();
    
//    /// Given the input positions, check if the object is picked (if the position falls within the menu).
//    int IsPicked(int pos1, int pos2);
    
    /// Get visibility of the object.
    int IsVisible();
    
//    /// Set activity indicator.
//    void SetActive(int is_active) { m_is_active = is_active; };
    
    /// Set the description text that precedes the input
    void SetDescriptionText(const char *description) { m_description.Assign(description); };
    
    /// Set size of font in the object.
    void SetFontSize(double font_size);
    
    /// Set pointer to clipboard.
    void SetClipBoard(vmxGUIClipBoard *clip_board) { m_clip_board = clip_board; };
    
    /// Set color of text in the object.
    void SetColor(double r, double g, double b);
    
    /// Set input text.
    void SetInputText(const char *text) { m_input.Assign(text); };
    
    /// Set the widget to input double numbers.
    void SetInputTypeToDoubleNumber(double default_value);

    /// Set the widget to input integer numbers.
    void SetInputTypeToIntegerNumber(int default_value);
    
    /// Set the widget to input dragged items.
    void SetInputTypeToItem();

    /// Set the widget to input any text.
    void SetInputTypeToText(const char *default_text);

    /// Set interactor.
    void SetInteractor(vtkRenderWindowInteractor *interactor);
    
    /// Set the origin (position) of the menu.
    void SetOrigin(int origin1, int origin2);
    
    /// Set visibility of the menu.
    void SetVisibility(int is_visible);
    
    /// Show the input text.
    int ShowInputText();
    
    
};



#endif
