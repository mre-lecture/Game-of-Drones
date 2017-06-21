using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Vuforia;

public class TargetScript : MonoBehaviour, ITrackableEventHandler
{

    public GameObject drohne;

	// Use this for initialization
	void Start () {
        
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}

    #region PUBLIC_METHODS

    /// <summary>
    /// Implementation of the ITrackableEventHandler function called when the
    /// tracking state changes.
    /// </summary>
    public void OnTrackableStateChanged(
                                    TrackableBehaviour.Status previousStatus,
                                    TrackableBehaviour.Status newStatus)
    {
        UnityEngine.Debug.Log("VM changed from " + previousStatus + " to " + newStatus);

        if (newStatus == TrackableBehaviour.Status.DETECTED ||
            newStatus == TrackableBehaviour.Status.TRACKED ||
            newStatus == TrackableBehaviour.Status.EXTENDED_TRACKED)
        {
            OnTrackingFound();
        }
        else
        {
            OnTrackingLost();
        }
    }

    #endregion // PUBLIC_METHODS



    #region PRIVATE_METHODS


    private void OnTrackingFound()
    {
        var counter = drohne.GetComponent<CounterScript>();
        counter.count++;
        counter.target = this.gameObject;
    }


    private void OnTrackingLost()
    {
        var counter = drohne.GetComponent<CounterScript>();
        counter.count--;
    }

    #endregion // PRIVATE_METHODS
}
