using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RotationScript : MonoBehaviour {

    public float YAxisRotationSpeed;
    
    // Update is called once per frame
    void Update () {
        this.transform.Rotate(0, YAxisRotationSpeed * Time.deltaTime, 0, Space.Self);
	}
}
