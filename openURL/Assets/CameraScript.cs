using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraScript : MonoBehaviour {

    GameObject drone;
    
	void Start () {
        drone = GameObject.FindGameObjectWithTag("drone");

    }
	
	void Update () {
        var cameraTransform = Camera.main.transform;
        transform.LookAt(drone.transform);
        this.transform.position += cameraTransform.forward * 0.01f;
        this.transform.position += cameraTransform.right * 0.01f;

        //this.transform.RotateAround(cameraTransform.position, cameraTransform.up, 5f);
        //this.transform.Rotate(Vector3.up, 20 * Time.deltaTime);

    }
}
