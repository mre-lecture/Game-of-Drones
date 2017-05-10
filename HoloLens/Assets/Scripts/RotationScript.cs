using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RotationScript : MonoBehaviour {

    public Vector3 RotationVector;
	
	// Update is called once per frame
	void Update () {
        this.transform.Rotate(RotationVector.x * Time.deltaTime, RotationVector.y * Time.deltaTime, RotationVector.z * Time.deltaTime, Space.Self);
	}
}
