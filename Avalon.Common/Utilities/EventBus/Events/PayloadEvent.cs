namespace Avalon.Common.Utilities.EventBus.Events
{
    /// <summary>
    /// Genereric event with Payload
    /// </summary>
    public class PayloadEvent<TPayload> : EventBase
    {
        public TPayload Payload { get; protected set; }

        public PayloadEvent(TPayload payload)
        {
            Payload = payload;
        }
    }
}