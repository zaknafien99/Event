#include "pch.h"

using namespace System;

// Delegates
delegate void FirstEventHandler(String^);
delegate void SecondEventHandler(String^);

//Event source class
ref class EvtSrc
{
public:
    // Declare the events
    event FirstEventHandler^ OnFirstEvent;
    event SecondEventHandler^ OnSecondEvent;

    // Event raisign functions
    void RaiseOne(String^ msg)
    {
        OnFirstEvent(msg);
    }

    void RaiseTwo(String^ msg)
    {
        OnSecondEvent(msg);
    }
};

// Event reeciver class
ref class EvtRcv
{
    EvtSrc^ theSource;
public:
    EvtRcv(EvtSrc^ src)
    {
        if(src == nullptr)
            throw gcnew ArgumentNullException("Must have event source");
        // Save the source
        theSource = src;

        //Add out handlers
        theSource->OnFirstEvent += gcnew FirstEventHandler(this, &EvtRcv::FirstEvent);
        theSource->OnSecondEvent += gcnew SecondEventHandler(this, &EvtRcv::SecondEvent);
    }

    // Handler functions
    void FirstEvent(String^ msg)
    {
        Console::WriteLine("EvtRcv: event one, message was {0}", msg);
    }

    void SecondEvent(String^ msg)
    {
        Console::WriteLine("EvtRcv: event two, message was {0}", msg);
    }

    // Remove a handler
    void RemoveHandler()
    {
        // remove the handler for the first event
        theSource->OnFirstEvent -= gcnew FirstEventHandler(this, &EvtRcv::FirstEvent);

       
    }
};


int main(array<System::String ^> ^args)
{
    Console::WriteLine("Event Example");

    // Create a source
    EvtSrc^ src = gcnew EvtSrc();

    // Create a receiver, and bind it to the source
    EvtRcv^ rcv = gcnew EvtRcv(src);

    // Fire events
    Console::WriteLine("Fire both events:");
    src->RaiseOne("Hello, mum!");
    src->RaiseTwo("One big step");
    // Remove the handler for event one
    rcv->RemoveHandler();

    // Fire events again
    Console::WriteLine("Fire both events:");
    src->RaiseOne("Hello, mum!");
    src->RaiseTwo("One big step");
    return 0;
}
