using HoloToolkit.Unity;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GestureHandler : Singleton<GestureHandler> {

    private bool isActive = false;

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		if (isActive)
        {
            this.transform.Rotate(0, 1, 0);
        }
	}

    void onAirTapped()
    {
        isActive = !isActive;
    }
}
