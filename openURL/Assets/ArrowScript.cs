using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;
using UnityEngine.VR.WSA.Input;

public class ArrowScript : MonoBehaviour {
    
    private GestureRecognizer recognizer;
    private UnityWebRequest request;
    private AsyncOperation op;

    public string tapUrl;
    private bool isGazed;

    // Use this for initialization
    void Start()
    {
        recognizer = new GestureRecognizer();
        recognizer.TappedEvent += Recognizer_TappedEvent;
        recognizer.StartCapturingGestures();

        isGazed = false;
    }

    // Update is called once per frame
    void Update()
    {
        transform.LookAt(Camera.main.transform);

        //Wenn Operation gestartet wurde
        if (op != null) {
            if(op.isDone)
            {
                UnityEngine.Debug.Log("Antwort: " + request.responseCode);
                op = null;
                request = null;
            } else
            {
                UnityEngine.Debug.Log("Fortschritt: " + request.downloadProgress + "/" + request.uploadProgress);
            }
        }
    }

    private void Recognizer_TappedEvent(InteractionSourceKind source, int tapCount, Ray headRay)
    {
        //Wenn Operation noch läuft, abbrechen
        if (op != null && !op.isDone)
            return;

        //Wenn Request bereits bearbeitet wurde, neuen erstellen
        if (request == null && isGazed)
            request = UnityWebRequest.Get(tapUrl);

        UnityEngine.Debug.Log("Sende request an " + request.url + " ("  + request.method + ")");
        op = request.Send();
    }

    void OnGazeEnter()
    {
        isGazed = true;
        Debug.Log(this.name + "ist fokussiert!");
    }

    void OnGazeExit()
    {
        isGazed = false;
        Debug.Log(this.name + "ist nicht mehr fokussiert!");
    }
}
