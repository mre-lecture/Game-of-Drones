using HoloToolkit.Unity.InputModule;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using UnityEngine.Networking;

public class MakeButtonsGreatAgain : MonoBehaviour, IFocusable, IInputClickHandler {
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
    void Start ()
    {
        gameObject.GetComponent<Renderer>().material.color = Color.gray;
    }

    bool wasDone = false;
    bool isDone = false;

	// Update is called once per frame
	void Update () {
        isDone = RequestDone;

        if (isDone && !wasDone)
        {
            gameObject.GetComponent<Renderer>().material.color = Color.green;
            request = null;
        }

        wasDone = isDone;
	}

    private void OnFocusChanged()
    {
        if (!RequestBusy)
        {
            if (this.focused)
            {
                gameObject.GetComponent<Renderer>().material.color = Color.yellow;
            }
            else
            {
                gameObject.GetComponent<Renderer>().material.color = Color.gray;
            }
        }
    }

    private void SendRequest()
    {
        request = UnityWebRequest.Get(TapUrl);
        op = request.Send();
    }

    public void OnInputClicked(InputClickedEventData eventData)
    {
        if (!focused || eventData.selectedObject != this.gameObject)
        {
            UnityEngine.Debug.Log("OnInputClicked: Not me! (" + this.gameObject.name + ")");
            return;
        }

        //Request null?
        if (RequestBusy)
        {
            UnityEngine.Debug.Log("Couldn't send request: Request already on its way");
        } else
        {
            SendRequest();
        }
    }
}
