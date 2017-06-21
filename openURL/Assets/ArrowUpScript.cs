using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.VR.WSA.Input;

public class ArrowUpScript : MonoBehaviour {

    Quaternion rotation;
    GestureRecognizer recognizer;

	// Use this for initialization
	void Start () {
        rotation = transform.rotation;

        recognizer = new GestureRecognizer();
        recognizer.TappedEvent += Recognizer_TappedEvent;
        recognizer.StartCapturingGestures();
    }
	
	// Update is called once per frame
	void Update () {
        transform.LookAt(Camera.main.transform);
    }

    private void LateUpdate()
    {
        transform.rotation = rotation;
    }

    private void Recognizer_TappedEvent(InteractionSourceKind source, int tapCount, Ray headRay)
    {
        Application.OpenURL("https://www.google.de/");
    }
}
