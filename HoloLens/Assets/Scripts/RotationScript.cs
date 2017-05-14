using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RotationScript : MonoBehaviour {

    public Vector3 Rotation;
	
	// Update is called once per frame
	void Update () {
        this.transform.Rotate(Rotation.x * Time.deltaTime, Rotation.y * Time.deltaTime, Rotation.z * Time.deltaTime, Space.Self);	
	}
}
