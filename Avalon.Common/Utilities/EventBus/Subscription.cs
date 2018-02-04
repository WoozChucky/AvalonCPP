using System;
using Avalon.Common.Utilities.EventBus.Events;
using Avalon.Common.Utilities.EventBus.Interfaces;

namespace Avalon.Common.Utilities.EventBus
{
    internal class Subscription<TEventBase> : ISubscription where TEventBase : EventBase
    {
        public SubscriptionToken SubscriptionToken { get; }

        public Subscription(Action<TEventBase> action, SubscriptionToken token)
        {
            _action = action ?? throw new ArgumentNullException(nameof(action));
            SubscriptionToken = token ?? throw new ArgumentNullException(nameof(token));
        }

        public void Publish(EventBase eventItem)
        {
            if (!(eventItem is TEventBase))
            {
                throw new ArgumentException("Event item is not correct type");
            }
            
            _action.Invoke((TEventBase) eventItem);
        }

        private readonly Action<TEventBase> _action;
    }
}