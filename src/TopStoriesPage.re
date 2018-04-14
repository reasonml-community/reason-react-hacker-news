open Utils;

type state = {
  topstories: HackerNews.stories,
  page: int,
  loading: bool
};

type action =
  | Loaded((int, HackerNews.stories))
  | Loading
  | Scroll;

let component = ReasonReact.reducerComponent("TopStoriesPage");
let make = (_children) => {

  let nearTheBottom = () => distanceFromBottom() < 100;
  let loadNextPage = ({ReasonReact.state, reduce}) =>
    if (state.page < 4) {
      HackerNews.fetchTopStories(state.page, reduce(payload => Loaded(payload))) |> ignore;
      reduce(() => Loading, ())
    };

  {
    ...component,

    initialState: () => {
      topstories: [||],
      page: 0,
      loading: false
    },

    reducer: (action, state) =>
      switch action {
      | Loading =>
        ReasonReact.Update({...state, loading: true})

      | Loaded((page, data)) =>
        let updatedTopstories = Array.concat([state.topstories, data]);
        ReasonReact.Update({
          topstories: updatedTopstories,
          page: page + 1,
          loading: false
        })

      | Scroll =>
        ReasonReact.SideEffects(self =>
          if (nearTheBottom() && !self.state.loading) {
            loadNextPage(self)
          }
        )
      },

    didMount: (self) => {
      Webapi.Dom.(Window.addEventListener("scroll", self.reduce((_) => Scroll), window));
      loadNextPage(self);
      ReasonReact.NoUpdate
    },

    render: (self) => {
      <div>
        (
          if (Array.length(self.state.topstories) > 0) {
            self.state.topstories
            |> Array.mapi((index, story) =>
              <StoryListItem key=(string_of_int(index)) index story />)
            |> arrayEl
          } else {
            ReasonReact.nullElement
          }
        )
      </div>
    }
  }
};
