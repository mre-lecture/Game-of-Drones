using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.VR.WSA.Input;

public class CubeManager : MonoBehaviour {

    public GameObject blueCubePrefab;

    GestureRecognizer recognizer;

	// Use this for initialization
	void Start () {
        recognizer = new GestureRecognizer();

        recognizer.TappedEvent += Recognizer_TappedEvent;

        recognizer.StartCapturingGestures();
	}

    private void Recognizer_TappedEvent(InteractionSourceKind source, int tapCount, Ray headRay) {
        var direction = headRay.direction;
        var origin = headRay.origin;
        var position = origin + direction * 2.0f;

        Instantiate(blueCubePrefab, position, Quaternion.identity);

        if (this != null)
        {
            this.SendMessage("OnAirTapped", SendMessageOptions.RequireReceiver);
        }
    }

    // Update is called once per frame
    void Update () {
		
	}
}
