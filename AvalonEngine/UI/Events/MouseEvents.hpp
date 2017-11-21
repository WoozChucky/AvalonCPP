#pragma once

namespace av
{
	namespace ui
	{
		namespace events
		{
			class MouseClickCallback
			{
				public:
				virtual ~MouseClickCallback() = default;
				virtual void Execute() = 0;
			};

			class MouseOverEnterCallback
			{
			public:
				virtual ~MouseOverEnterCallback() = default;
				virtual void Execute() = 0;
			};

			class MouseOverExitCallback
			{
			public:
				virtual ~MouseOverExitCallback() = default;
				virtual void Execute() = 0;
			};
		}
	}
}

