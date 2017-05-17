using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.VR.WSA.Input;

public class CubeManager : MonoBehaviour {

    public GameObject greenCubePrefab;

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

        Instantiate(greenCubePrefab, position, Quaternion.identity);
    }

    // Update is called once per frame
    void Update () {
		
	}
}
