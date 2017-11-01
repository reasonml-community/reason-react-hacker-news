open ReasonJs;

open Utils;

type state = {
  topstories: StoryData.topstories,
  page: int,
  loading: bool
};

type action =
  | Loaded((int, StoryData.topstories))
  | Loading
  | Scroll;

let component = ReasonReact.reducerComponent("TopStoriesPage");

let make = (_children) => {
  let nearTheBottom = () => distanceFromBottom() < 100;
  let loadNextPage = ({ReasonReact.state, reduce}) =>
    if (state.page < 4) {
      StoryData.fetchTopStories(state.page, reduce((payload) => Loaded(payload))) |> ignore;
      reduce(() => Loading, ())
    };
  {
    ...component,
    initialState: fun () => ({topstories: [||], page: 0, loading: false}: state),
    reducer: (action, state) =>
      switch action {
      | Loading => ReasonReact.Update({...state, loading: true})
      | Loaded((page, data)) =>
        let updatedTopstories = Array.concat([state.topstories, data]);
        ReasonReact.Update({topstories: updatedTopstories, page: page + 1, loading: false})
      | Scroll =>
        ReasonReact.SideEffects(
          (
            (self) =>
              if (nearTheBottom() && ! self.state.loading) {
                loadNextPage(self)
              }
          )
        )
      },
    didMount: (self) => {
      Dom.(Window.addEventListener("scroll", self.reduce((_) => Scroll), window));
      loadNextPage(self);
      ReasonReact.NoUpdate
    },
    render: (self) => {
      let storyArray =
        if (Array.length(self.state.topstories) > 0) {
          Array.mapi(
            (index, story) => <StoryListItem key=(string_of_int(index)) index story />,
            self.state.topstories
          )
        } else {
          [||]
        };
      <div> (ReasonReact.arrayToElement(storyArray)) </div>
    }
  }
};
