using HoloToolkit.Unity.InputModule;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using UnityEngine.Networking;

public class MakeButtonsGreatAgain : MonoBehaviour, IFocusable, IInputClickHandler
{
    private bool focused;
    private UnityWebRequest request;
    private AsyncOperation op;

    public string TapUrl = "http://hs-mannheim.de/";

    public bool IsFocused
    {
        get { return focused; }
        set
        {
            if (focused != value)
            {
                focused = value;
                OnFocusChanged();
            }
        }
    }

    public bool RequestBusy
    {
        get
        {
            return RequestInitialized && !op.isDone;
        }
    }

    public bool RequestDone
    {
        get
        {
            return RequestInitialized && op.isDone;
        }
    }

    public bool RequestInitialized
    {
        get
        {
            return request != null && op != null;
        }
    }

    public void OnFocusEnter()
    {
        IsFocused = true;
    }

    public void OnFocusExit()
    {
        IsFocused = false;
    }

    // Use this for initialization
    void Start()
    {
        ChangeColor(Color.white);
    }

    bool wasDone = false;
    bool isDone = false;

    // Update is called once per frame
    void Update()
    {
        isDone = RequestDone;

        if (isDone && !wasDone)
        {
            request = null;
            ChangeColor(Color.white);
        }

        wasDone = isDone;
    }

    private void ChangeColor(Color c )
    {
        var renderers = gameObject.GetComponentsInChildren<Renderer>();
        foreach (var renderer in renderers)
            renderer.material.color = c;
    }

    private void OnFocusChanged()
    {
        UnityEngine.Debug.Log("OnFocusChanged: " + this.gameObject.name);
        if (!RequestBusy)
        {
            ChangeColor(focused? Color.green : Color.white);
        } else
        {
            UnityEngine.Debug.Log("OnFocusChanged -> RequestBusy: " + this.gameObject.name);
        }
    }

    private void SendRequest()
    {
        UnityEngine.Debug.Log("SendRequest: " + this.gameObject.name + " to " + TapUrl);
        request = UnityWebRequest.Get(TapUrl);
        op = request.Send();

        ChangeColor(Color.clear);
    }

    public void OnInputClicked(InputClickedEventData eventData)
    {
        UnityEngine.Debug.Log("OnInputClicked: " + this.gameObject.name);

        //Request null?
        if (RequestBusy)
        {
            UnityEngine.Debug.Log("Couldn't send request: Request already on its way");
        }
        else
        {
            SendRequest();
        }
    }
}
