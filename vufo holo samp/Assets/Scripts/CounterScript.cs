using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CounterScript : MonoBehaviour {

    public int count;
    public GameObject target;

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update ()
    {
        if (count > 0 && (target != null && target.activeSelf))
        {
            this.gameObject.transform.position = target.transform.position;
            this.gameObject.transform.rotation = target.transform.rotation;
            var angles = this.gameObject.transform.eulerAngles;

            this.gameObject.transform.rotation = Quaternion.Euler(angles.x, angles.y - 60, angles.z);
        }
        var renderers = this.gameObject.GetComponents<Renderer>();
        foreach (var renderer in renderers)
            renderer.enabled = count > 0;
    }
}
