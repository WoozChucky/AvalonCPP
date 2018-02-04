using Avalon.Common.Utilities.EventBus.Events;

namespace Avalon.Common.Utilities.EventBus.Interfaces
{
    public interface ISubscription
    {
        /// <summary>
        /// Token return to the subscriber
        /// </summary>
        SubscriptionToken SubscriptionToken { get; }

        /// <summary>
        /// Publish to the subscriber
        /// </summary>
        /// <param name="eventBase"></param>
        void Publish(EventBase eventBase);
    }
}