/*=========================================================================
 
 Program:   mipx
 Module:    vmxGUIInteractorStyleImage.cpp
 
 Authors: Danilo Babin.
 Copyright (c) Danilo Babin.
 All rights reserved.
 See Copyright.txt
 
 Licensed under the BSD License 2.0.
 
 This software is distributed WITHOUT ANY WARRANTY; without even
 the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 PURPOSE. See the above copyright notice for more information.
 
 =========================================================================*/




#include "vmxGUIInteractorStyleImage.h"


int vmxGUIInteractorStyleImage::EventDoubleClick = vtkCommand::UserEvent + 1;


vmxGUIInteractorStyleImage::vmxGUIInteractorStyleImage()
{
    m_registered_renderer_3D = NULL;
    m_left_button_down_picked_renderer = NULL;
    m_is_double_clicked = 0;
    m_is_left_button_down = 0;
    m_picked_2D_actor_on_left_button_down = NULL;
    this->EventDoubleClick = vtkCommand::UserEvent + 1;
}


vmxGUIInteractorStyleImage::~vmxGUIInteractorStyleImage()
{
    
}


vmxGUIInteractorStyleImage* vmxGUIInteractorStyleImage::New()
{
    return new vmxGUIInteractorStyleImage;
}


//void vmxGUIInteractorStyleImage::OnMouseMove()
//{
//    if(m_is_left_button_down && m_picked_2D_actor_on_left_button_down)
//    {
////        if(m_picked_2D_actor_on_left_button_down)
////        {
////            // do nothing
////        }
////        else
////        {
////            //m_registered_renderer_2D
////        }
//    }
//    else
//    {
//        int* clickPos = this->GetInteractor()->GetEventPosition();
//        this->FindPokedRenderer(clickPos[0], clickPos[1]);
//        cout<<" "<<((void*)this->CurrentRenderer)<<" ";
//        
//        if(m_registered_renderer_2D != this->CurrentRenderer)
//        {
//            vtkInteractorStyleTrackballCamera::OnMouseMove();
//        }
//    }
//}


void vmxGUIInteractorStyleImage::OnMouseMove()
{
    if(m_is_left_button_down)// && m_picked_2D_actor_on_left_button_down)
    {
        if(!m_picked_2D_actor_on_left_button_down)
        {
            int* clickPos = this->GetInteractor()->GetEventPosition();
            this->FindPokedRenderer(clickPos[0], clickPos[1]);
            cout<<" "<<((void*)this->CurrentRenderer)<<" ";
            
            if(m_registered_renderer_3D == this->CurrentRenderer && m_left_button_down_picked_renderer==this->CurrentRenderer)
            {
                cout<<" & ";
                vtkInteractorStyleTrackballCamera::OnMouseMove();
                return;
            }
            //else
            {
                cout<<" * ";
                //vtkInteractorStyleImage::OnMouseMove();
            }
        }
        //else do nothing
        
    }
//    else
//    {
//        vtkInteractorStyleImage::OnMouseMove();
//    }
}



void vmxGUIInteractorStyleImage::OnLeftButtonUp()
{
    m_is_left_button_down = 0;
    vtkInteractorStyleImage::OnLeftButtonUp();
}


void vmxGUIInteractorStyleImage::OnLeftButtonDown()
{
    m_time_of_left_click_in_ms2 = std::chrono::time_point_cast<std::chrono::milliseconds>(clock::now());
    
    long time_diff = (m_time_of_left_click_in_ms2 - m_time_of_left_click_in_ms).count();
    m_time_of_left_click_in_ms = m_time_of_left_click_in_ms2;
    
    //cout<<" time_diff="<<time_diff<<"  ";
    
    //std::cout << "Pressed left mouse button." << std::endl;
    this->m_number_of_clicks++;
    //std::cout << "NumberOfClicks = " << this->NumberOfClicks << std::endl;
    
    
    m_is_left_button_down = 1;
    
    
    vtkRenderWindowInteractor *rwi = this->Interactor;
    
    int pickPosition[2];
    rwi->GetEventPosition(pickPosition);
    
    int xdist = pickPosition[0] - m_left_button_down_previous_position[0];
    int ydist = pickPosition[1] - m_left_button_down_previous_position[1];
    
    m_left_button_down_previous_position[0] = pickPosition[0];
    m_left_button_down_previous_position[1] = pickPosition[1];
    
    int moveDistance = (int)sqrt((double)(xdist*xdist + ydist*ydist));
    
    // Reset numClicks - If mouse moved further than resetPixelDistance
    if(moveDistance > 5 || time_diff>700)//this->ResetPixelDistance)
    {
        this->m_number_of_clicks = 1;
        m_is_double_clicked = 0;
    }
    
    
    if(this->m_number_of_clicks == 2)
    {
        std::cout <<this->EventDoubleClick;
        this->m_number_of_clicks = 0;
        //rwi->GetPicker()->
        m_is_double_clicked = 1;
        
        //this->InvokeEvent(this->EventDoubleClick, NULL);
        this->InvokeEvent(this->EventDoubleClick, NULL);
        std::cout << " # ";
        
        //vtkCommand::UserEvent
        //m_menu->GetPickedItem(rwi->GetEventPosition()[0],rwi->GetEventPosition()[1]);
    }
    
    
    int* clickPos = this->GetInteractor()->GetEventPosition();
    
    // Pick from this location.
    vtkSmartPointer<vtkPropPicker>  picker =
    vtkSmartPointer<vtkPropPicker>::New();
    picker->PickProp(clickPos[0], clickPos[1], rwi->GetRenderWindow()->GetRenderers()->GetFirstRenderer());
    
    double* pos = picker->GetPickPosition();
    std::cout << "Pick position (world coordinates) is: "
    << pos[0] << " " << pos[1]
    << " " << pos[2] << std::endl;
    
    std::cout << "Picked actor: " << picker->GetActor2D() << std::endl;
    
    m_picked_2D_actor_on_left_button_down = picker->GetActor2D();
    
    
    this->FindPokedRenderer(clickPos[0], clickPos[1]);
    cout<<" "<<((void*)this->CurrentRenderer)<<" ";
    
    m_left_button_down_picked_renderer = this->CurrentRenderer;
    
    if (this->CurrentRenderer == m_registered_renderer_3D)
    {
        //std::cout << "Nothing selected." << std::endl;
        vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
        return;
    }
    
    // forward events
    vtkInteractorStyleImage::OnLeftButtonDown();
}


void vmxGUIInteractorStyleImage::OnKeyPress()
{
    //get the keypress
    vtkRenderWindowInteractor *rwi = this->Interactor;
    std::string key = rwi->GetKeySym();
    
    if(key.compare("a") == 0)
    {
        //cout<<" a ";
        //m_v_img->SetIndexTime(m_v_img->GetIndexTime()+1);
        rwi->Render();
    }
    if(key.compare("z") == 0)
    {
        //cout<<" z ";
        //m_v_img->SetIndexTime(m_v_img->GetIndexTime()-1);
        rwi->Render();
    }
    if(key.compare("s") == 0)
    {
        //cout<<" s ";
        //m_v_img->SetIndexSlices(m_v_img->GetIndexSlices()+1);
        rwi->Render();
    }
    if(key.compare("x") == 0)
    {
        //cout<<" x ";
        //m_v_img->SetIndexSlices(m_v_img->GetIndexSlices()-1);
        rwi->Render();
    }
    if(key.compare("q") == 0)
    {
        //m_tree->ReleaseAllDataObjects();
        rwi->GetRenderWindow()->Finalize();
        
        // Stop the interactor
        rwi->TerminateApp();
    }
    if(key.compare("p") == 0)
    {
        cout<<"event_pos="<<rwi->GetEventPosition()[0]<<","<< rwi->GetEventPosition()[1]<<"   ";
        //m_menu->GetPickedItem(rwi->GetEventPosition()[0],rwi->GetEventPosition()[1]);
        
        //            m_tree->ReleaseAllDataObjects();
        //            rwi->GetRenderWindow()->Finalize();
        //            //
        //            //    // Stop the interactor
        //            rwi->TerminateApp();
    }
}

